// memory_cost_mod.cpp
// Cross-platform small tool to allocate big memory blocks and stress-access them
// Linux: uses getrusage to read minor/major faults. Windows: script collects PageFaults externally.
//
// Build: cmake .. && cmake --build . -- -j

#if defined(_WIN32)
    #include <iostream>
    #include <filesystem>
    #include <fstream>
    #include <vector>
    #include <string>
    #include <algorithm>
    #include <chrono>
    #include <thread>
    #include <random>
    #include <iomanip>
    #include <cmath>
    #include <windows.h>
    #include <psapi.h>
#else
    #include <bits/stdc++.h>
  #include <sys/resource.h>
  #include <unistd.h>
#endif

namespace fs = std::filesystem;
using namespace std;

struct Config {
    size_t block_size = 1000000; // ints per block
    int threads = 1;
    int allocations = 1;
    string pattern = "seq"; // seq, rand, stride
    size_t stride = 16;
    int duration = 10; // seconds
    string output = "results/memory_results.csv";
};

Config cfg;

#if !defined(_WIN32)
long get_minor_faults() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_minflt;
}
long get_major_faults() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_majflt;
}
#endif

void worker_thread(int id) {
    vector<vector<int>> blocks;
    blocks.reserve(cfg.allocations);
    for (int a = 0; a < cfg.allocations; ++a) {
        try {
            blocks.emplace_back(vector<int>(cfg.block_size));
        } catch (bad_alloc &e) {
            cerr << "Thread " << id << " allocation failed: " << e.what() << endl;
            return;
        }
    }

    // Touch pages initially to map them
    for (auto &b : blocks) {
        for (size_t i = 0; i < b.size(); i += max<size_t>(1, cfg.stride)) b[i] = (int)i;
    }

    auto end_time = chrono::steady_clock::now() + chrono::seconds(cfg.duration);
    mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count() + id);
    while (chrono::steady_clock::now() < end_time) {
        for (auto &b : blocks) {
            if (cfg.pattern == "seq") {
                for (size_t i = 0; i < b.size(); i += max<size_t>(1, cfg.stride)) b[i]++;
            } else if (cfg.pattern == "rand") {
                for (int i = 0; i < 1000; ++i) {
                    size_t idx = (size_t)(rng() % b.size());
                    b[idx]++;
                }
            } else if (cfg.pattern == "stride") {
                for (size_t i = 0; i < b.size(); i += max<size_t>(1, cfg.stride)) b[i]++;
            }
            this_thread::sleep_for(chrono::microseconds(10));
        }
    }
    // end -> destructor free memory
}

void print_usage() {
    cout << "Usage: memory_cost_mod --size <ints_per_block> --allocs <num_blocks> --threads <n> "
         << "--pattern [seq|rand|stride] --stride <s> --duration <s> --output <file>\n";
}

int main(int argc, char** argv) {
    for (int i=1;i<argc;i++){
        string a = argv[i];
        if (a=="--size" && i+1<argc) cfg.block_size = stoull(argv[++i]);
        else if (a=="--allocs" && i+1<argc) cfg.allocations = stoi(argv[++i]);
        else if (a=="--threads" && i+1<argc) cfg.threads = stoi(argv[++i]);
        else if (a=="--pattern" && i+1<argc) cfg.pattern = argv[++i];
        else if (a=="--stride" && i+1<argc) cfg.stride = stoull(argv[++i]);
        else if (a=="--duration" && i+1<argc) cfg.duration = stoi(argv[++i]);
        else if (a=="--output" && i+1<argc) cfg.output = argv[++i];
        else if (a=="--help") { print_usage(); return 0; }
    }

    cout << "Config: size="<<cfg.block_size<<" allocs="<<cfg.allocations
         <<" threads="<<cfg.threads<<" pattern="<<cfg.pattern
         <<" stride="<<cfg.stride<<" duration="<<cfg.duration<<endl;

#if !defined(_WIN32)
    long min_before = get_minor_faults();
    long maj_before = get_major_faults();
#endif

    auto t0 = chrono::steady_clock::now();
    vector<thread> th;
    for (int i=0;i<cfg.threads;i++) th.emplace_back(worker_thread, i);
    for (auto &t : th) if (t.joinable()) t.join();
    auto t1 = chrono::steady_clock::now();

#if !defined(_WIN32)
    long min_after = get_minor_faults();
    long maj_after = get_major_faults();
    long min_delta = min_after - min_before;
    long maj_delta = maj_after - maj_before;
    cout << "minflt delta: " << min_delta << " majflt delta: " << maj_delta << endl;
#else
    long min_delta = -1, maj_delta = -1;
    cout << "Windows OS: use external monitor (Process Explorer / Get-Process) for page faults." << endl;
#endif

    double dur = chrono::duration<double>(t1-t0).count();
    // ensure results dir exists
    fs::path outp(cfg.output);
    fs::create_directories(outp.parent_path());


    ofstream out(cfg.output, ios::app);
    // header if empty
    if (out.tellp() == 0) {
        out << "threads,allocs,block_size,pattern,stride,duration,elapsed,minflt_delta,majflt_delta\n";
    }
    out << cfg.threads << "," << cfg.allocations << "," << cfg.block_size << "," << cfg.pattern << "," << cfg.stride << "," << cfg.duration << "," << dur << ",";
    out << min_delta << "," << maj_delta << "\n";
    out.close();

    cout << "Finished in " << dur << " s, saved to " << cfg.output << endl;
    return 0;
}
