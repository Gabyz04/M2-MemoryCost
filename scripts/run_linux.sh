#!/usr/bin/env bash
# Usage: ./scripts/run_linux.sh <threads> <blocksize_ints> <allocs> <pattern> <stride> <duration>
set -e

THREADS=${1:-4}
BLOCKSIZE=${2:-1000000}
ALLOCS=${3:-1}
PATTERN=${4:-seq}
STRIDE=${5:-16}
DUR=${6:-20}

# Build all
echo "=== Compilando projeto ==="
cmake -S . -B build
cmake --build build -- -j

# Create results folder
mkdir -p results

# MemoryCost
echo "=== Executando MemoryCost ==="
./build/MemoryCost/memory_cost_mod \
  --size $BLOCKSIZE --allocs $ALLOCS --threads $THREADS --pattern $PATTERN --stride $STRIDE --duration $DUR \
  --output results/memory_results_linux.csv

# ThreadsStress
echo "=== Executando ThreadsStress ==="
./build/ThreadsStress/threads_stress_mod $THREADS $BLOCKSIZE $DUR

# SortingStress
echo "=== Executando SortingStress ==="
./build/SortingStress/ordenacao_stress
