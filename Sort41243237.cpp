#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ==================== Insertion Sort ====================
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int j = 1; j < n; j++) {
        int key = arr[j];
        int i = j - 1;
        while (i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

// ==================== Quick Sort ====================
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    swap(arr[mid], arr[high - 1]);
    return arr[high - 1];
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low, j = high - 1;
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[high - 1]);
    return i;
}

void quickSort(vector<int>& arr, int low, int high) {
    while (low + 10 <= high) {
        int pivotIndex = partition(arr, low, high);
        if (pivotIndex - low < high - pivotIndex) {
            quickSort(arr, low, pivotIndex - 1);
            low = pivotIndex + 1;
        }
        else {
            quickSort(arr, pivotIndex + 1, high);
            high = pivotIndex - 1;
        }
    }
}

void quickSort(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// ==================== Merge Sort ====================
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            merge(arr, left, mid, right);
        }
    }
}


// ==================== Heap Sort ====================
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ==================== 測試 ====================
void testtime(vector<int> arr, void (*sortFunc)(vector<int>&), string sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " took " << duration.count() << " microseconds." << endl;
}

// ==================== 主程式 ====================
int main() {
    vector<int> sizes = { 500, 1000, 2000, 4000, 5000, 10000, 50000 };
    srand(time(0));

    for (int n : sizes) {
        cout << "\n===== Sorting for n = " << n << " =====" << endl;
        vector<int> arr(n);
        for (int& x : arr)
            x = rand() % 10000 + 1;

        cout << "\nSorting for n = " << n << endl;
        testtime(arr, insertionSort, "Insertion Sort");
        testtime(arr, quickSort, "Quick Sort");
        testtime(arr, mergeSort, "Merge Sort");
        testtime(arr, heapSort, "Heap Sort");

    }

    return 0;
}
