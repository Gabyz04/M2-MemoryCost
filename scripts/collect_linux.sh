#!/usr/bin/env bash
# collect vmstat/top while process runs
OUTDIR=results/collects_$(date +%Y%m%d_%H%M%S)
mkdir -p $OUTDIR
vmstat 1 ${1:-10} > $OUTDIR/vmstat.txt &
VMSTATPID=$!
top -b -n ${2:-5} -d 1 > $OUTDIR/top.txt
kill $VMSTATPID || true
echo "Saved vmstat/top to $OUTDIR"
