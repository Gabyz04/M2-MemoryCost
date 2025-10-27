#!/usr/bin/env bash
# run_linux.sh <threads> <blocksize_ints> <allocs> <pattern> <stride> <duration>
set -e
THREADS=${1:-4}
BLOCKSIZE=${2:-1000000}
ALLOCS=${3:-1}
PATTERN=${4:-seq}
STRIDE=${5:-16}
DUR=${6:-20}

# Build
cmake -S . -B build && cmake --build build -- -j

# drop caches (requires sudo)
if [ "$(id -u)" -eq 0 ]; then
  echo 3 > /proc/sys/vm/drop_caches
else
  echo "Not root: skipping drop_caches (run sudo to drop caches for reproducibility)"
fi

mkdir -p results
./build/MemoryCost/memory_cost_mod --size $BLOCKSIZE --allocs $ALLOCS --threads $THREADS --pattern $PATTERN --stride $STRIDE --duration $DUR --output results/memory_results.csv
