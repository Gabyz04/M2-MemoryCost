// SortingStress/ordenacao_stress.cpp
// Wrapper to stress memory using sorting
// Usage: ./ordenacao_stress <vec_size> <threads> <repetitions>

#include <bits/stdc++.h>
#include "algOrdenacao.hpp"
using namespace std;

void worker(size_t vec_size, int repetitions, int id) {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() + id);
    for (int r = 0; r < repetitions; ++r) {
        vector<int> v;
        try {
            v.resize(vec_size);
        } catch(...) {
            cerr << "Alloc failed for vec_size="<<vec_size<<endl;
            return;
        }
        for (size_t i = 0; i < v.size(); ++i) v[i] = (int)(rng() % 1000000000);
        // use std::sort to reduce algorithm variance and still stress memory/cache
        sort(v.begin(), v.end());
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main(int argc, char** argv) {
    size_t vec_size = 5000000;
    int threads = 1;
    int repetitions = 1;
    if (argc > 1) vec_size = stoull(argv[1]);
    if (argc > 2) threads = stoi(argv[2]);
    if (argc > 3) repetitions = stoi(argv[3]);

    cout<<"vec_size="<<vec_size<<" threads="<<threads<<" reps="<<repetitions<<endl;
    vector<thread> th;
    for (int t=0; t<threads; ++t) th.emplace_back(worker, vec_size, repetitions, t);
    for (auto &tt : th) if (tt.joinable()) tt.join();
    return 0;
}
