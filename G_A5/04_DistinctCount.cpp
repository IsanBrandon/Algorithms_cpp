#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

// --------------------------------------------------
// 방법 1. Hashing + Sliding Window
// 평균 시간복잡도: O(n)
// 공간복잡도: O(k)
// --------------------------------------------------
void solveByHashing(const vector<int>& A, int k) {
    unordered_map<int, int> freq;
    int n = A.size();
    int distinct = 0;

    for (int i = 0; i < k; i++) {
        if (freq[A[i]] == 0)
            distinct++;

        freq[A[i]]++;
    }

    cout << "[Hashing] ";
    cout << distinct << " ";

    for (int right = k; right < n; right++) {
        int left = right - k;

        freq[A[left]]--;

        if (freq[A[left]] == 0) {
            distinct--;
            freq.erase(A[left]);
        }

        if (freq[A[right]] == 0)
            distinct++;

        freq[A[right]]++;

        cout << distinct << " ";
    }

    cout << endl;
}

// --------------------------------------------------
// 방법 2. Red-Black Tree 기반 map + Sliding Window
// 시간복잡도: O(n log k)
// 공간복잡도: O(k)
// --------------------------------------------------
void solveByMap(const vector<int>& A, int k) {
    map<int, int> freq;
    int n = A.size();
    int distinct = 0;

    for (int i = 0; i < k; i++) {
        if (freq[A[i]] == 0)
            distinct++;

        freq[A[i]]++;
    }

    cout << "[Map] ";
    cout << distinct << " ";

    for (int right = k; right < n; right++) {
        int left = right - k;

        freq[A[left]]--;

        if (freq[A[left]] == 0) {
            distinct--;
            freq.erase(A[left]);
        }

        if (freq[A[right]] == 0)
            distinct++;

        freq[A[right]]++;

        cout << distinct << " ";
    }

    cout << endl;
}

// --------------------------------------------------
// 방법 3. 완전탐색 + set
// 시간복잡도: O((n-k+1) * k log k)
// 공간복잡도: O(k)
// --------------------------------------------------
void solveByBruteForceSet(const vector<int>& A, int k) {
    int n = A.size();

    cout << "[Brute Force + Set] ";

    for (int start = 0; start <= n - k; start++) {
        set<int> s;

        for (int i = start; i < start + k; i++) {
            s.insert(A[i]);
        }

        cout << s.size() << " ";
    }

    cout << endl;
}

// --------------------------------------------------
// main 함수
// 입력 예시:
// 7
// 1 2 1 3 4 2 3
// 4
// --------------------------------------------------
int main() {
    int n;
    cin >> n;

    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int k;
    cin >> k;

    solveByHashing(A, k);
    solveByMap(A, k);
    solveByBruteForceSet(A, k);

    return 0;
}