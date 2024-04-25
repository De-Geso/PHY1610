#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --time=0:10:00
#SBATCH --output=parallel_output.txt
#SBATCH --mail-type=FAIL

for i in {1..16}
do
    source teachsetup
    export OMP_NUM_THREADS=$i
    echo $OMP_NUM_THREADS
    time ./laplace
    echo ""
done
