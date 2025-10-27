// threads_stress_mod.cpp
// Simple program to spawn threads, allocate large vector per thread and touch memory.
//
// Build: cmake && make

#include <bits/stdc++.h>
#if !defined(_WIN32)
  #include <sys/resource.h>
#endif
using namespace std;

int main(int argc, char** argv){
    int threads = 4;
    size_t per_thread = 2000000; // ints
    int duration = 10;
    if (argc>1) threads = stoi(argv[1]);
    if (argc>2) per_thread = stoull(argv[2]);
    if (argc>3) duration = stoi(argv[3]);

    cout<<"threads="<<threads<<" per_thread="<<per_thread<<" duration="<<duration<<endl;
    vector<thread> th;
    for (int t=0;t<threads;t++){
        th.emplace_back([t,per_thread,duration](){
            vector<int> v;
            try{ v.assign(per_thread, 0); } catch(...) { cerr<<"alloc fail\n"; return;}
            auto end=chrono::steady_clock::now()+chrono::seconds(duration);
            mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count()+t);
            while (chrono::steady_clock::now()<end){
                // touch memory with stride
                for (size_t i=0;i<v.size(); i+=64) v[i]++;
                // small random touches
                for (int k=0;k<10;k++) v[rng()%v.size()]++;
                this_thread::sleep_for(chrono::microseconds(50));
            }
        });
    }
    for (auto &t: th) if (t.joinable()) t.join();
#if !defined(_WIN32)
    struct rusage ru; getrusage(RUSAGE_SELF, &ru);
    cout<<"minflt="<<ru.ru_minflt<<" majflt="<<ru.ru_majflt<<endl;
#endif
    return 0;
}
