#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>

#define DEBUG 0

const size_t PARALLEL_THRESHOLD = 10000;

void generateMergeSortData(std::vector<int>& arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        arr[i] = rand();
    }
}

void checkMergeSortResult(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            std::cerr << "non bene" << std::endl;
            return;
        }
    }
}

void merge(int* arr, size_t l, size_t m, size_t r, int* temp) {
    size_t i = l;
    size_t j = m;
    size_t k = 0;

    while (i < m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < m) {
        temp[k++] = arr[i++];
    }
    while (j <= r) {
        temp[k++] = arr[j++];
    }
    for (i = l, k = 0; i <= r; ++i, ++k) {
        arr[i] = temp[k];
    }
}

void sequential_mergesort(int* arr, size_t l, size_t r, int* temp) {
    if (l < r) {
        size_t m = l + (r - l) / 2;
        sequential_mergesort(arr, l, m, temp);
        sequential_mergesort(arr, m + 1, r, temp);

        std::vector<int> merge_temp(r - l + 1);
        merge(arr, l, m + 1, r, merge_temp.data());
    }
}

void parallel_mergesort(int* arr, size_t l, size_t r, int* temp, size_t threshold) {
    if (l >= r) return;

    if (r - l < threshold) {
        sequential_mergesort(arr, l, r, temp);
        return;
    }

    size_t m = l + (r - l) / 2;

    std::thread left_thread;
    if (r - l > threshold * 2) {
        left_thread = std::thread(parallel_mergesort, arr, l, m, temp, threshold);
    } else {
        sequential_mergesort(arr, l, m, temp);
    }

    parallel_mergesort(arr, m + 1, r, temp, threshold);

    if (left_thread.joinable()) {
        left_thread.join();
    }

    std::vector<int> merge_temp(r - l + 1);
    merge(arr, l, m + 1, r, merge_temp.data());
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "You need to have : " << argv[0] << " <n>  to execute this program" << std::endl;
        return -1;
    }

    // command line parameter
    size_t n = atol(argv[1]);

    // get arr data
    std::vector<int> arr(n);
    generateMergeSortData(arr, n);

#if DEBUG
    std::cout << "Before sort: ";
    for (auto num : arr) std::cout << num << " ";
    std::cout << std::endl;
#endif

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> temp (n);
    if (n > PARALLEL_THRESHOLD) {
        parallel_mergesort(arr.data(), 0, n - 1, temp.data(), PARALLEL_THRESHOLD);
    } else {
        sequential_mergesort(arr.data(), 0, n - 1, temp.data());
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cerr << "Sorting array of " << argv[1] << " elements took: " << elapsed.count() << " seconds" << std::endl;

    checkMergeSortResult(arr);

#if DEBUG
    std::cout << "After sort: ";
    for (auto num : arr) std::cout << num << " ";
    std::cout << std::endl;
#endif

    return 0;
}
