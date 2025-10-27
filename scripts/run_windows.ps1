# PowerShell script to build and run on Windows, sampling Get-Process
param(
    [int]$threads = 4,
    [int]$blocksize = 1000000,
    [int]$allocs = 1,
    [string]$pattern = "seq",
    [int]$stride = 16,
    [int]$duration = 20
)

# Build (assumes cmake & Visual Studio or mingw in PATH)
Write-Host "Building..."
cmake -S . -B build
cmake --build build --config Release

$exe = Join-Path -Path (Get-Location) -ChildPath "build\MemoryCost\memory_cost_mod.exe"
if (-Not (Test-Path $exe)) {
    Write-Host "Executable not found: $exe"
    exit 1
}

$arg = "--size $blocksize --allocs $allocs --threads $threads --pattern $pattern --stride $stride --duration $duration --output results\memory_results_win.csv"
Write-Host "Starting: $exe $arg"
$proc = Start-Process -FilePath $exe -ArgumentList $arg -PassThru

# sample PageFaults and WorkingSet every second
$outFile = "results\memsample_$(Get-Date -Format yyyyMMdd_HHmmss).csv"
"timestamp,PageFaults,WorkingSet" | Out-File -FilePath $outFile
for ($i=0; $i -lt $duration; $i++) {
    try {
        $p = Get-Process -Id $proc.Id -ErrorAction Stop
        "$((Get-Date).ToString('o')),$($p.PageFaults),$($p.WorkingSet64)" | Out-File -FilePath $outFile -Append
    } catch {
        break
    }
    Start-Sleep -Seconds 1
}
Write-Host "Sampling saved to $outFile"
