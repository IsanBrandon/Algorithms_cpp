#include <iostream>
using namespace std;

int N, W;
int w[20], v[20], c[20];
int best = -1000000000;

void solve(int idx, int currentVolume, int currentScore) {
    // 모든 물건을 다 처리한 경우
    if (idx == N) {
        if (currentScore > best)
            best = currentScore;
        return;
    }

    // 경우 1: 현재 물건을 버린다
    solve(idx + 1, currentVolume, currentScore - c[idx]);

    // 경우 2: 현재 물건을 가져간다 (가능할 때만)
    if (currentVolume + w[idx] <= W) {
        solve(idx + 1,
              currentVolume + w[idx],
              currentScore + v[idx]);
    }
}

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    cin >> W;

    solve(0, 0, 0);

    cout << best << '\n';
    return 0;
}



