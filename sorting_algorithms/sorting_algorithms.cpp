#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

#include "Timer.h"

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
// QUICK SORT
uint32_t Partition(int* arr, int start, int end) {
    uint32_t middle_index = start + (end - start) / 2;
    uint32_t temp_index_01 = arr[start] <= arr[middle_index] ? start : middle_index;
    uint32_t temp_index_02 = arr[middle_index] <= arr[end] ? middle_index : end;
    uint32_t pivot_index = arr[temp_index_01] >= arr[temp_index_02] ? temp_index_01 : temp_index_02;
    
    Swap(arr[pivot_index], arr[end]);
    int pivot = arr[end];
    uint32_t ptr = start;

    for (uint32_t i = ptr; i < end; i++) {
        if (arr[i] <= pivot) {
            Swap(arr[ptr], arr[i]);
            ptr++;
        }
    }
    Swap(arr[ptr], arr[end]);

    return ptr;
}
void QuickSort(int* arr, int start, int end) {
    if (start < end) {
        uint32_t pivot_index = Partition(arr, start, end);

        QuickSort(arr, start, pivot_index - 1);
        QuickSort(arr, pivot_index + 1, end);
    }
}
// MERGE SORT
void Merge(int* arr, uint32_t const start, const uint32_t mid, const uint32_t end) {
    uint32_t left_array_size = mid - start + 1;
    uint32_t right_array_size = end - mid;

    int* left_array = new int[left_array_size];
    int* right_array = new int[right_array_size];

    for (uint32_t i = 0; i < left_array_size; i++)
        left_array[i] = arr[start + i];
    for (uint32_t i = 0; i < right_array_size; i++)
        right_array[i] = arr[mid + i + 1];

    uint32_t left_index = 0, right_index = 0, merged_index = start;
    while (left_index < left_array_size && right_index < right_array_size) {
        if (left_array[left_index] <= right_array[right_index]) {
            arr[merged_index] = left_array[left_index];
            left_index++;
        }
        else {
            arr[merged_index] = right_array[right_index];
            right_index++;
        }
        merged_index++;
    }
    for (uint32_t i = left_index; i < left_array_size; i++)
        arr[merged_index++] = left_array[i];
    for (uint32_t i = right_index; i < right_array_size; i++)
        arr[merged_index++] = right_array[i];

    delete[] left_array;
    delete[] right_array;
}
void MergeSort(int* arr, uint32_t const start, uint32_t const end) {
    if (start >= end)
        return;
    uint32_t mid = start + (end - start) / 2;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);

    Merge(arr, start, mid, end);
}
// HEAP SORT
void Heapify(int* arr, uint32_t n, uint32_t root) {
    uint32_t largest = root;
    uint32_t left = 2 * root + 1;
    uint32_t right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        Swap(arr[root], arr[largest]);

        Heapify(arr, n, largest);
    }
}
void HeapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    for (uint32_t i = n - 1; i > 0; i--) {
        Swap(arr[0], arr[i]);

        Heapify(arr, i, 0);
    }
}
// TIM SORT
void InsertionSort(int* arr, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        for (int j = i - 1; j >= start; j--) {
            if (arr[j] < arr[j + 1])
                break;
            Swap(arr[j], arr[j + 1]);
        }
    }
}
const int RUN = 32;
void TimSort(int* arr, uint32_t n) {
    for (uint32_t i = 0; i < n; i += RUN)
        InsertionSort(arr, i, std::min((int)(i + RUN - 1), (int)(n - 1)));

    for (uint32_t size = RUN; size < n; size *= 2) {
        for (uint32_t left = 0; left < n; left += 2 * size) {
            uint32_t mid = left + size - 1;
            uint32_t right = std::min(int(left + 2 * size - 1), int(n - 1));

            if (mid < right)
                Merge(arr, left, mid, right);
        }
    }
}
void CopyArray(int* src, int* dst, int n) {
    for (uint32_t i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}
void PrintArray(int* arr, int n) {
    for (uint32_t i = 0; i < n; i++) {
        std::cout << arr[i] << "\n";
    }
}
void GenerateArrayData(int* arr, int* backup, int n) {
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(-1, 1);
    // ready to generate random numbers
    const int MAX = 10000;
    for (int i = 0; i < n; i++)
    {
        double currentRandomNumber = unif(rng);
        arr[i] = currentRandomNumber * MAX;
        backup[i] = currentRandomNumber * MAX;
    }
}

void Sort(int* arr, int n, int index) {
    if (index == 0)
        QuickSort(arr, 0, n - 1);
    else if (index == 1)
        MergeSort(arr, 0, n - 1);
    else if (index == 2)
        HeapSort(arr, n);
    else if (index == 3)
        TimSort(arr, n);
    else
        std::cout << "Invalid index!" << "\n";
}

const int n = 1000000;
int array[n];
int backup[n];

int main()
{
    GenerateArrayData(array, backup, n);

    std::ofstream file("output_01.csv");
    int step = 5000;
    for (uint32_t bound = step; bound <= n; bound += step) {
        file << bound << ", ";
    }
    file << "\n";

    for (uint32_t algorithm_index = 0; algorithm_index < 4; algorithm_index++) {
        for (uint32_t bound = step; bound <= n; bound += step) {

            Timer timer;
            uint32_t test_count = 1;
            float time_millis = 0;
            for (uint32_t i = 0; i < test_count; i++) {
                timer.Reset();
                Sort(array, bound, algorithm_index);

                time_millis += timer.ElapsedMillis();
                //std::cout << timer.ElapsedMillis() << std::endl;

                CopyArray(backup, array, bound);
            }
            time_millis = time_millis / test_count;
            //std::cout << time_millis << "\n";

            file << time_millis << ",";
        }
        std::cout << "sort finished\n";
        file << "\n";
    }



    //PrintArray(backup, n);
    std::cout << "--------------------------------------------------\n";
    //PrintArray(array, n);
}