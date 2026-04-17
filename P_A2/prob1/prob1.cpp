//  Total words: 125,553
//  ---------- Sorting Times ----------
//  Bubble Sort: 0.0036808 sec
//  Insertion Sort: 337.581 sec
//  Merge Sort: 1.26245 sec
//  Quick Sort (last pivot): 6e-07 sec
//  Heap Sort: 0.3449 sec
//  Library Sort: 0.108119 sec
//  -----------------------------------

#include <iostream>     // cout, cin 사용
#include <fstream>      // 파일 읽기 (ifstream)
#include <sstream>      // 문자열 분리 (stringstream)
#include <vector>       // vector 사용
#include <string>       // string 사용
#include <algorithm>    // sort (표준 라이브러리 정렬)
#include <chrono>       // 시간 측정

using namespace std;

// ------------------------------
// 버블 정렬
// ------------------------------
void bubbleSort(vector<string>& arr) {   // 원본 배열을 직접 수정하기 위해 참조 사용
    int n = (int)arr.size();             // 배열 크기 저장

    for (int i = 0; i < n - 1; i++) {    // 전체 패스 반복 (n-1번)
        for (int j = 0; j < n - i - 1; j++) {  // 뒤에서 i개는 이미 정렬됨
            if (arr[j] > arr[j + 1]) {   // 현재 값이 다음 값보다 크면
                swap(arr[j], arr[j + 1]); // 두 값을 교환
            }
        }
    }
}

// ------------------------------
// 삽입 정렬
// ------------------------------
void insertionSort(vector<string>& arr) {
    int n = (int)arr.size();

    for (int i = 1; i < n; i++) {        // 두 번째 원소부터 시작
        string key = arr[i];             // 현재 삽입할 값 저장
        int j = i - 1;                   // 이전 위치부터 비교 시작

        while (j >= 0 && arr[j] > key) { // key보다 큰 값들을 오른쪽으로 이동
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;                // 올바른 위치에 key 삽입
    }
}

// ------------------------------
// 병합 정렬 - merge 함수
// ------------------------------
void merge(vector<string>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;             // 왼쪽 부분 배열 크기
    int n2 = right - mid;                // 오른쪽 부분 배열 크기

    vector<string> L(n1), R(n2);         // 임시 배열 생성

    for (int i = 0; i < n1; i++)         // 왼쪽 배열 복사
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)         // 오른쪽 배열 복사
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;          // i: L, j: R, k: 원본 배열

    while (i < n1 && j < n2) {           // 두 배열 비교
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];           // 작은 값을 넣고 인덱스 증가
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)                       // 남은 L 처리
        arr[k++] = L[i++];

    while (j < n2)                       // 남은 R 처리
        arr[k++] = R[j++];
}

// ------------------------------
// 병합 정렬 - 재귀 함수
// ------------------------------
void mergeSort(vector<string>& arr, int left, int right) {
    if (left >= right) return;           // 원소가 1개면 종료

    int mid = (left + right) / 2;        // 중간 위치 계산

    mergeSort(arr, left, mid);           // 왼쪽 정렬
    mergeSort(arr, mid + 1, right);      // 오른쪽 정렬

    merge(arr, left, mid, right);        // 병합
}

// ------------------------------
// 퀵 정렬 - partition
// ------------------------------
int partition(vector<string>& arr, int low, int high) {
    string pivot = arr[high];            // 마지막 원소를 pivot으로 선택
    int i = low - 1;                     // 작은 값들의 마지막 위치

    for (int j = low; j < high; j++) {   // 전체 순회
        if (arr[j] < pivot) {            // pivot보다 작으면
            i++;
            swap(arr[i], arr[j]);        // 앞쪽으로 이동
        }
    }

    swap(arr[i + 1], arr[high]);         // pivot을 가운데로 이동
    return i + 1;                        // pivot 위치 반환
}

// ------------------------------
// 퀵 정렬
// ------------------------------
void quickSort(vector<string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // 분할 위치

        quickSort(arr, low, pi - 1);         // 왼쪽 정렬
        quickSort(arr, pi + 1, high);        // 오른쪽 정렬
    }
}

// ------------------------------
// 힙 정렬 - heapify
// ------------------------------
void heapify(vector<string>& arr, int n, int i) {
    int largest = i;                 // 가장 큰 값
    int left = 2 * i + 1;            // 왼쪽 자식
    int right = 2 * i + 2;           // 오른쪽 자식

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);  // 부모와 교환
        heapify(arr, n, largest);    // 재귀적으로 heap 유지
    }
}

// ------------------------------
// 힙 정렬
// ------------------------------
void heapSort(vector<string>& arr) {
    int n = (int)arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) // 최대 힙 구성
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);       // 최대값을 뒤로 이동
        heapify(arr, i, 0);         // 힙 재구성
    }
}

// ------------------------------
// 메인 함수
// ------------------------------
int main() {
    ifstream file("harry_full.txt");    // 파일 열기
    vector<string> original;            // 원본 데이터 저장
    string word;

    while (file >> word) {              // 단어 단위로 읽기
        original.push_back(word);       // 벡터에 저장
    }

    file.close();                       // 파일 닫기

    vector<string> arr;

    // ------------------------------
    // Bubble Sort
    // ------------------------------
    arr = original; // 동일한 데이터 복사 (공정한 비교)
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto end = chrono::high_resolution_clock::now();
    cout << "Bubble Sort: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    // ------------------------------
    // Insertion Sort
    // ------------------------------
    arr = original;
    start = chrono::high_resolution_clock::now();
    insertionSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Insertion Sort: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    // ------------------------------
    // Merge Sort
    // ------------------------------
    arr = original;
    start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    end = chrono::high_resolution_clock::now();
    cout << "Merge Sort: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    // ------------------------------
    // Quick Sort
    // ------------------------------
    arr = original;
    start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    end = chrono::high_resolution_clock::now();
    cout << "Quick Sort: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    // ------------------------------
    // Heap Sort
    // ------------------------------
    arr = original;
    start = chrono::high_resolution_clock::now();
    heapSort(arr);
    end = chrono::high_resolution_clock::now();
    cout << "Heap Sort: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    // ------------------------------
    // STL sort
    // ------------------------------
    arr = original;
    start = chrono::high_resolution_clock::now();
    sort(arr.begin(), arr.end());  // C++ 표준 정렬
    end = chrono::high_resolution_clock::now();
    cout << "STL sort: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    return 0;
}