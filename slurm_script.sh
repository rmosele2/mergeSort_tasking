#!/bin/bash
#SBATCH --job-name=mergeSort
#SBATCH --partition=Centaurus
#SBATCH --time=00:20:00
#SBATCH --mem-per-cpu=10g
#SBATCH --output=results.txt

module purge
module load gcc/11.2.0

SIZES=(100 1000 10000 100000 1000000 10000000)

echo "Benchmarking Parallel vs Sequential Merge Sort" > results.txt

for size in "${SIZES[@]}"
do
  echo "Array size: $size" >> results.txt

  echo -n "Sequential: " >> results.txt
  $HOME/ITCS4145/mergeSort_tasking/mergesort_seq $size >> results.txt

  echo -n "Parallel: " >> results.txt
  $HOME/ITCS4145/mergeSort_tasking/mergesort_par $size >> results.txt

  echo "" >> results.txt
done
