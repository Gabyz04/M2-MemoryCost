# M2 - Page Fault Analysis (Integrated Project)

Repository contains three modules:
- `MemoryCost/` — adapted memory stress tool (multi-threaded, patterns)
- `ThreadsStress/` — simple threads memory pressure tool
- `SortingStress/` — sorting-based memory stress (adapted from the provided sorting code)
- `scripts/` — run and collect scripts for Linux and Windows
- `results/` — outputs (CSV, samples)
- `docs/relatorio.md` — report template

## Build (Linux / Codespaces)
```bash
git clone <repo-url>
mkdir build && cd build
cmake ..
cmake --build . -- -j
# or from repo root:
cmake -S . -B build && cmake --build build -- -j

## Run Examples Linux
sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"
./build/MemoryCost/memory_cost_mod --size 1000000 --allocs 2 --threads 4 --pattern seq --stride 16 --duration 30 --output results/memory_results.csv


## Run Examples Windows
pwsh .\scripts\run_windows.ps1 -threads 4 -blocksize 1000000 -allocs 2 -pattern seq -stride 16 -duration 30
