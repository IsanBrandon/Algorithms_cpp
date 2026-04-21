#include <iostream>
#include <cstdlib>
using namespace std;

int nearest (int arr[], int start, int end, int N, int K) {
    if (start > end) {
        if (end < 0) return arr[0];
        if (start >= N) return arr[N-1];
    
        int left = arr[end];    // K보다 작은 쪽 
        int right = arr[start]; // K보다 큰 쪽 

        if (abs(K - left) <= abs(K - right))
            return left;
        else
            return right; 
    }

    int mid = (start + end) / 2;

    if (arr[mid] == K) return arr[mid];
    else if (K < arr[mid]) return nearest(arr, start, mid - 1, N, K);
    else return nearest(arr, mid + 1, end, N, K);
}

int main() {
    int N, K; int arr[1000];

    cin >> N; for (int i = 0; i < N; i++) cin >> arr[i]; cin >> K;

    cout << nearest(arr, 0, N - 1, N, K);
    
    return 0;
}

