# mergeSort_tasking
## Description
This project implements and compares **sequential** and **parallel** versions of merge sort in C++. The parallel implementation uses `std::thread` and applies multithreading only when array size exceeds a defined threshold.

## Files
- `mergesort_seq_nocopy.cpp`: Sequential merge sort.
- `mergesort_parallel.cpp`: Parallel merge sort with dynamic thresholding.
- `Makefile`: Builds both versions (`mergesort_seq` and `mergesort_par`).
- `slurm_script.sh`: SLURM script for benchmarking on Centaurus.
- `results.txt`: Output file containing performance results.

## Compilation
```bash
make
