#include <iostream>
using namespace std;

int n;
int a[20];

bool canReach(int idx) {
    // 마지막 칸에 정확히 도착
    if (idx == n - 1)
        return true;

    // 범위를 벗어나면 실패
    if (idx >= n)
        return false;

    // 0에 도착했는데 마지막 칸이 아니면 더 못 감
    if (a[idx] == 0)
        return false;

    // 현재 칸에서 가능한 점프들을 모두 시도
    for (int jump = 1; jump <= a[idx]; jump++) {
        if (canReach(idx + jump))
            return true;
    }

    return false;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    if (canReach(0))
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}

