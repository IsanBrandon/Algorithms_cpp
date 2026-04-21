#include <iostream>
using namespace std;

int countRank (int arr[], int N, int K, int index) {
    if (index == N) return 0;

    if (arr[index] < K)
        return 1 + countRank(arr, N, K, index + 1); 
    else
        return countRank(arr, N, K, index + 1);
} 

int main() {
    int N, K;
    int arr[1000];

    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    cin >> K; 

    int rank = countRank(arr, N, K, 0) + 1;
    cout << rank;

    return 0;
}

