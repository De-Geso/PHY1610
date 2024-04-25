#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks=32
#SBATCH --time=0:05:00
#SBATCH --output=mpi_output.txt

source teachsetup
for i in 1 4 16 32
do
    echo P=$i
    time mpirun -n $i ./random_batch
    echo ""
done
