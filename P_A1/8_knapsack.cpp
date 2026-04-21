#include <iostream>
using namespace std;

int N, W;
int w[16], v[16];
int answer = 0;

void knapsack(int idx, int currentWeight, int currentValue) {
    // 현재까지 만든 가치가 더 크면 정답 갱신
    if (currentValue > answer)
        answer = currentValue;

    // 모든 아이템을 다 본 경우 종료
    if (idx == N)
        return;

    // 경우 1: 현재 아이템을 선택하지 않음
    knapsack(idx + 1, currentWeight, currentValue);

    // 경우 2: 현재 아이템을 선택함 (가능할 때만)
    if (currentWeight + w[idx] <= W) {
        knapsack(idx + 1,
                 currentWeight + w[idx],
                 currentValue + v[idx]);
    }
}

int main() {
    cin >> N;
    cin >> W;

    for (int i = 0; i < N; i++)
        cin >> w[i];

    for (int i = 0; i < N; i++)
        cin >> v[i];

    knapsack(0, 0, 0);

    cout << answer << '\n';
    return 0;
}



