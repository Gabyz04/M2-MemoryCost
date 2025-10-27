param(
    [int]$threads = 4,
    [int]$blocksize = 1000000,
    [int]$allocs = 1,
    [string]$pattern = "seq",
    [int]$stride = 16,
    [int]$duration = 20
)

# Build all
Write-Host "=== Compilando projeto ==="
cmake -S . -B build
cmake --build build --config Release

# Results folder
$resultsFolder = "results"
if (-Not (Test-Path $resultsFolder)) { New-Item -ItemType Directory -Path $resultsFolder }

# MemoryCost
$memExe = Join-Path -Path $PWD -ChildPath "build\MemoryCost\Release\memory_cost_mod.exe"
$memArgs = "--size $blocksize --allocs $allocs --threads $threads --pattern $pattern --stride $stride --duration $duration --output $resultsFolder\memory_results_win.csv"
Write-Host "`n=== Executando MemoryCost ==="
& $memExe $memArgs

# ThreadsStress
$threadExe = Join-Path -Path $PWD -ChildPath "build\ThreadsStress\Release\threads_stress_mod.exe"
Write-Host "`n=== Executando ThreadsStress ==="
& $threadExe $threads $blocksize $duration

# SortingStress
$sortExe = Join-Path -Path $PWD -ChildPath "build\SortingStress\Release\ordenacao_stress.exe"
Write-Host "`n=== Executando SortingStress ==="
& $sortExe
