
# 排序演算法報告

**41243217 杜長勳  41243222 林諺晟**  
APR. 25 / 2025  

## 目錄

1. [解題說明](#解題說明)
2. [演算法設計與實作](#演算法設計與實作)
3. [效能分析](#效能分析)
4. [測試與結果](#測試與結果)
5. [結論](#結論)

---

## 解題說明

本報告實作並比較了五種常見排序演算法的效能：

- **插入排序（Insertion Sort）**
- **選擇排序（Selection Sort）**
- **快速排序（Quick Sort）**
- **合併排序（Merge Sort）**
- **堆疊排序（Heap Sort）**

測試目標為分析各演算法在不同輸入大小下的執行時間，並探討其效能特性。

---

## 演算法設計與實作

### 插入排序 (Insertion Sort)
插入排序的核心思想是將資料一一插入已排序的部分：
```cpp
// 插入排序實作
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

### 選擇排序 (Selection Sort)
```cpp
// 選擇排序實作
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
```

### 快速排序 (Quick Sort)
```cpp
// 快速排序主程式（含閾值優化）
void quickSort(vector<int>& arr, int low, int high) {
    if (low + 10 <= high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    } else {
        insertionSort(arr);
    }
}

// 三數取中 pivot
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    swap(arr[mid], arr[high - 1]);
    return arr[high - 1];
}
```

### 合併排序 (Merge Sort)
```cpp
// 迭代式合併排序
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
```

### 堆疊排序 (Heap Sort)
```cpp
// 堆排序實作
void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

---

## 效能分析

### 時間複雜度比較

| 演算法 | 最佳情況 | 平均情況 | 最壞情況 |
|---------|---------|---------|---------|
| 插入排序 | O(n) | O(n^2) | O(n^2) |
| 選擇排序 | O(n^2) | O(n^2) | O(n^2) |
| 快速排序 | O(n log n) | O(n log n) | O(n^2) |
| 合併排序 | O(n log n) | O(n log n) | O(n log n) |
| 堆疊排序 | O(n log n) | O(n log n) | O(n log n) |

### 空間複雜度

| 演算法       | 空間複雜度         |
|--------------|--------------------|
| 插入排序     | O(1)               |
| 選擇排序     | O(1)               |
| 快速排序     | O(log n)（最壞 O(n)） |
| 合併排序     | O(n)               |
| 堆疊排序       | O(1)               |

### 穩定性分析

| 演算法       | 穩定性   |
|--------------|----------|
| 插入排序     | ✅ 穩定  |
| 選擇排序     | ❌ 不穩定 |
| 快速排序     | ❌ 不穩定 |
| 合併排序     | ✅ 穩定  |
| 堆疊排序       | ❌ 不穩定 |

### 效能趨勢觀察

1. **O(n^2) 演算法**：隨資料量增加，執行時間呈二次方增長。
2. **O(n log n) 演算法**：隨資料量增加，成長速度較平緩，適合大型資料集。

---

## 測試與結果

測試使用不同大小的隨機整數陣列（500 至 50000 元素），使用 `chrono` 計時工具測量每種排序演算法執行時間。

```cpp
void testSorting(vector<int>& arr, void (*sortFunc)(vector<int>&), string sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " took " << duration.count() << " ms." << endl;
}
```

### 測試結果

![image](https://github.com/user-attachments/assets/61bf8fc4-f088-43f6-bb75-2af333ee5761)

---
| n       | Insertion Sort | Selection Sort | Quick Sort | Merge Sort | Heap Sort |
|---------|----------------|----------------|-------------|-------------|-------------|
| 500     | 0 ms           | 0 ms           | 0 ms        | 1 ms        | 0 ms        |
| 1000    | 2 ms           | 3 ms           | 2 ms        | 3 ms        | 0 ms        |
| 2000    | 12 ms          | 14 ms          | 15 ms       | 6 ms        | 0 ms        |
| 4000    | 45 ms          | 60 ms          | 31 ms       | 16 ms       | 1 ms        |
| 5000    | 72 ms          | 112 ms         | 95 ms       | 15 ms       | 1 ms        |
| 10000   | 292 ms         | 389 ms         | 339 ms      | 30 ms       | 5 ms        |
| 50000   | 7120 ms        | 9289 ms        | 8013 ms     | 154 ms      | 23 ms       |


![image](https://github.com/user-attachments/assets/47e297e1-6e68-4ab1-9dd7-81cdeb214855)


---

## 結論

### 小資料集（n < 100）
- 插入排序效率優秀，實作簡單。
- 快速排序的「小陣列改插入排序」優化，提升了其在小資料的表現。

### 大資料集
- **快速排序** 通常表現最佳，但需注意最壞情況。
- **合併排序** 在效能與穩定性之間取得良好平衡。
- **堆排序** 雖然速度略慢，但空間使用少，適合記憶體受限情境。

### 應用建議總結

| 情境              | 推薦演算法   |
|-------------------|----------------|
| 小型資料           | 插入排序       |
| 資料近乎有序       | 插入排序       |
| 一般情況最佳效能   | 快速排序       |
| 穩定排序需求       | 合併排序       |
| 記憶體使用需嚴格控制 | 堆疊排序         |

---
