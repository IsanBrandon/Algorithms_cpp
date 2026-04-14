/*  Total words: 125,553
 *  ---------- Sorting Times ----------
 *  Bubble Sort: 0.0036808 sec
 *  Insertion Sort: 337.581 sec
 *  Merge Sort: 1.26245 sec
 *  Quick Sort (last pivot): 6e-07 sec
 *  Heap Sort: 0.3449 sec
 *  Library Sort: 0.108119 sec
 *  -----------------------------------
 */

#include <iostream>     // cout, cerr
#include <fstream>      // ifstream
#include <vector>       // vector
#include <string>       // string
#include <chrono>       // for time measurement
#include <algorithm>    // swap, sort for library sort

using namespace std;
using namespace chrono; // chrono::high_resolution_clock 같은 시간 관련 이름을 간단히 쓰기 위해

// ---------------- Bubble Sort ---------------- 
// 인접한 두 원소를 비교하며 큰 값을 오른쪽으로 밀어가는 방식
void bubbleSort(vector<string>& arr) {          // 배열을 참조로 받아서 직접 정렬한다. (복사본이 아니라 원본을 수정)
    int n = (int)arr.size();                    // C++17에서는 size()가 size_t이므로 명시적으로 int로 형변환 해줘야
    for (int i = 0; i < n - 1; i++) {           // n-1번 반복 & 매 번 마다 가장 큰 원소 하나가 맨 뒤로 이동 
        bool swapped = false;                   // 이 번 반복에서 교환이 일어났는지 체크하는 플래그 - 이미 정렬된 경우 불필요한 반복을 줄이기 위해
        for (int j = 0; j < n - 1 - i; i++) {   // 뒤쪽 i개 구간은 이미 정렬이 끝났으니 볼 필요가 없어서 n - 1 - i까지만 돈다.
            if (arr[j] > arr[j + 1]) {          // 예: "zebra" > "apple"이면 자리 바꿈이 필요하다.
                swap(arr[j], arr[j + 1]);       // 두 문자열의 위치를 교환
                swapped = true;                 // 교환이 일어났음을 표시. 만약 이 반복이 끝날 때까지 swapped가 false라면 이미 정렬이 완료된 상태이므로 더 이상 반복할 필요가 없다.
            }
        }
        if (!swapped) break;                    // 한 번도 교환이 없었다면 이미 정렬 완료 상태이므로 반복 종료
    }
}

// ---------------- Insertion Sort ----------------
void insertionSort(vector<string>& arr) {
    int n = (int)arr.size();
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ---------------- Merge Sort ----------------
void merge(vector<string>& arr, int left, int mid, int right) {
    vector<string> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < (int)temp.size(); k++) {
        arr[left + k] = temp[k];
    }
}

void mergeSort(vector<string>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ---------------- Quick Sort (last pivot) ----------------
int partitionLastPivot(vector<string>& arr, int left, int right) {
    string pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quickSort(vector<string>& arr, int left, int right) {
    if (left < right) return;
    int p = partitionLastPivot(arr, left, right);
    quickSort(arr, left, p - 1);
    quickSort(arr, p + 1, right);
}

// ---------------- Heap Sort ----------------
void heapify(vector<string>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); 
    }
}

void heapSort(vector<string>& arr) {
    int n = (int)arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0); 
    }
}

// ---------------- Time Measurement Helper ----------------
template <typename Func>
double measureSortTime(const vector<string>& original, Func sortFunc) {
    vector<string> arr = original;

    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

int main() {
    ifstream fin("harry_full.txt");
    if (!fin) { cerr << "Error opening file!\n"; return 1; }

    vector<string> original;
    string word;
    while (fin >> word) { original.push_back(word); }
    fin.close();

    cout << "Total words: " << original.size() << "\n\n";

    double t1 = measureSortTime(original, [](vector<string>& a) { bubbleSort(a);});
    cout << "Bubble Sort: " << t1 << " sec\n";

    double t2 = measureSortTime(original, [](vector<string>& a) { insertionSort(a);});
    cout << "Insertion Sort: " << t2 << " sec\n";

    double t3 = measureSortTime(original, [](vector<string>& a) { mergeSort(a, 0, (int)a.size() - 1);});
    cout << "Merge Sort: " << t3 << " sec\n";

    double t4 = measureSortTime(original, [](vector<string>& a) { quickSort(a, 0, (int)a.size() - 1);});
    cout << "Quick Sort (last pivot): " << t4 << " sec\n";

    double t5 = measureSortTime(original, [](vector<string>& a) { heapSort(a);});
    cout << "Heap Sort: " << t5 << " sec\n";

    double t6 = measureSortTime(original, [](vector<string>& a) { sort(a.begin(), a.end());});
    cout << "Library Sort: " << t6 << " sec\n";

    return 0;
}