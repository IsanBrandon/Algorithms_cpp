#include <iostream>
using namespace std;

int N, K;
int A[16][16];
int selected[16];
int best = -1000000000;

void choose(int idx, int selectedCount, int currentScore) {
    // k명을 다 뽑았으면 정답 갱신
    if (selectedCount == K) {
        if (currentScore > best)
            best = currentScore;
        return;
    }

    // 모든 선수를 다 봤는데 k명을 못 채웠으면 종료
    if (idx == N)
        return;
        
    // 남은 선수를 전부 뽑아도 k명을 못 채우면 종료
    if (selectedCount + (N - idx) < K)
        return;

    // 경우 1: idx번 선수를 뽑는다
    int addScore = A[idx][idx];
    for (int i = 0; i < selectedCount; i++) {
        int p = selected[i];
        addScore += A[p][idx] + A[idx][p];
    }

    selected[selectedCount] = idx;
    choose(idx + 1, selectedCount + 1, currentScore + addScore);

    // 경우 2: idx번 선수를 뽑지 않는다
    choose(idx + 1, selectedCount, currentScore);
}

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    cin >> K;

    choose(0, 0, 0);

    cout << best << '\n';
    return 0;
}




