#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#define DEBUG 0
const size_t PARALLEL_THRESHOLD = 10000;

void generateMergeSortData (std::vector<int>& arr, size_t n) {
  for (size_t  i = 0; i < n; ++i) {
    arr[i] = rand();
  }
}

void checkMergeSortResult (std::vector<int>& arr, size_t n) {
    for (size_t  i = 1; i < n; ++i) {
        if (arr[i]< arr[i-1]) {
            std::cerr<<"notok"<<std::endl;
            return;
        }
    }
}

void merge (int * arr, size_t  l, size_t  mid, size_t r, int* temp) {
    if (l == r) {
        return;
    }
    if (r-l == 1) {
        if (arr[l] > arr[r]) {
           std::swap(arr[l], arr[r]);
        }
        return;
    }

    size_t n = mid - l;
    for (size_t i = 0; i < n; ++i) {
        temp[i] = arr[l+i];
    }

    size_t i = 0;
    size_t j = mid;
    size_t k = l;
    while (i < n && j <= r) {
        arr[k++] = (temp[i] <= arr[j]) ? temp[i++] : arr[j++];
    }

    while (i < n) {
        arr[k++] = temp[i++];
    }
}

void parallelMergeSort (int * arr, size_t l, size_t r, int* temp) {
    if (l < r) {
        size_t mid = (l + r) / 2;
        if ((r - l + 1) >= PARALLEL_THRESHOLD) {
            std::vector<int> temp_left(mid - l + 1);
            std::vector<int> temp_right(r - mid);
            std::thread left_thread(parallelMergeSort, arr, l, mid, temp_left.data());
            std::thread right_thread(parallelMergeSort, arr, mid + 1, r, temp_right.data());
            left_thread.join();
            right_thread.join();
        } else {
            parallelMergeSort(arr, l, mid, temp);
            parallelMergeSort(arr, mid + 1, r, temp);
        }       
        merge(arr, l, mid + 1, r, temp);
    }
}

int main (int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return -1;
    }

    size_t n = std::strtoul(argv[1], nullptr, 10);
    std::vector<int> arr(n);
    generateMergeSortData(arr, n);

    std::vector<int> temp(n);

    auto start = std::chrono::high_resolution_clock::now();
    parallelMergeSort(arr.data(), 0, n - 1, temp.data());
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cerr << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;

    checkMergeSortResult(arr, n);
    return 0;
}