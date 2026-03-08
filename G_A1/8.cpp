#include <iostream>
using namespace std;

int main() {
    int n;
    int arr[100];

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    bool seen[100] = {false}; // 현재 구간 안에 등장한 숫자인지 기록
    int left = 0;             // 현재 구간의 왼쪽 끝
    int max_len = 0;          // 최대 길이 저장

    for (int right = 0; right < n; right++) {
        // arr[right]가 이미 현재 구간 안에 있으면
        // 중복이 없어질 때까지 왼쪽을 줄인다
        while (seen[arr[right]]) {
            seen[arr[left]] = false;
            left++;
        }

        // 이제 arr[right]를 넣어도 중복이 없음
        seen[arr[right]] = true;

        // 현재 중복 없는 구간의 길이 계산
        int len = right - left + 1;

        // 최대 길이 갱신
        if (len > max_len) {
            max_len = len;
        }
    }

    cout << max_len << endl;
    return 0;
}