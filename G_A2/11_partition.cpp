#include <iostream>   // 입력(cin), 출력(cout)을 사용하기 위한 헤더
using namespace std;

// 정수 개수의 최대 크기
// 필요하면 더 크게 늘릴 수 있다.
const int MAXN = 100;

// 입력으로 주어지는 정수의 개수
int n;

// 입력된 정수들을 저장할 배열
int arr[MAXN];

// 전체 정수들의 합
int totalSum = 0;

// 우리가 만들어야 하는 목표 합
// 전체 합이 짝수일 때 totalSum / 2 가 된다.
int target = 0;

// selected[i] == true  : arr[i]를 첫 번째 집합(A)에 넣는다.
// selected[i] == false : arr[i]를 두 번째 집합(B)에 넣는다.
bool selected[MAXN];


// ------------------------------------------------------------
// partitionBacktrack(index, currentSum)
// ------------------------------------------------------------
// 의미:
//   arr[0] ~ arr[index-1] 까지에 대해서는
//   이미 A에 넣을지 B에 넣을지 결정한 상태라고 하자.
//   그때 현재 A집합의 합이 currentSum일 때,
//   arr[index]부터 끝까지 적절히 선택해서
//   최종적으로 target을 만들 수 있는지 검사한다.
//
// 매개변수:
//   index      : 지금 결정하려는 원소의 인덱스
//   currentSum : 현재까지 A집합에 들어간 원소들의 합
//
// 반환값:
//   true  -> target을 만들 수 있음
//   false -> target을 만들 수 없음
// ------------------------------------------------------------
bool partitionBacktrack(int index, int currentSum) {

    // [기저 조건 1]
    // 현재까지 만든 합이 정확히 목표값 target이면 성공이다.
    // 즉, A집합의 합이 target이 되었으므로
    // 나머지 원소들은 자동으로 B집합으로 가면 된다.
    if (currentSum == target) {
        return true;
    }

    // [기저 조건 2]
    // 현재 합이 이미 target을 넘었다면 실패다.
    //
    // 이 가지치기는 "입력이 음이 아닌 정수"라고 볼 때 유효하다.
    // 왜냐하면 앞으로 더 원소를 추가하면 합은 더 커지기만 하고,
    // 다시 줄어들 수 없기 때문이다.
    if (currentSum > target) {
        return false;
    }

    // [기저 조건 3]
    // 모든 원소를 다 살펴봤는데도 target을 만들지 못했다면 실패다.
    if (index == n) {
        return false;
    }

    // --------------------------------------------------------
    // 경우 1: arr[index]를 A집합에 넣는 경우
    // --------------------------------------------------------

    // 현재 원소를 A집합에 포함시켰음을 기록
    selected[index] = true;

    // 다음 원소로 넘어가면서
    // currentSum에 arr[index]를 더한 값을 넘긴다.
    if (partitionBacktrack(index + 1, currentSum + arr[index])) {
        // 만약 이 선택으로 성공했다면
        // 더 이상 다른 경우를 볼 필요 없이 true 반환
        return true;
    }

    // --------------------------------------------------------
    // 경우 2: arr[index]를 A집합에 넣지 않는 경우
    // --------------------------------------------------------
    // 즉, 이 원소는 B집합에 들어간다고 생각하면 된다.

    // 현재 원소를 A집합에 넣지 않았음을 기록
    selected[index] = false;

    // 현재 합(currentSum)은 그대로 둔 채 다음 원소로 진행
    if (partitionBacktrack(index + 1, currentSum)) {
        // 이 경우가 성공하면 true 반환
        return true;
    }

    // --------------------------------------------------------
    // 위 두 경우가 모두 실패했다면
    // 현재 상태에서는 답을 만들 수 없다는 뜻
    // --------------------------------------------------------
    return false;
}

int main() {
    // 정수의 개수 입력
    cin >> n;

    // n개의 정수를 입력받아 배열에 저장하고,
    // 동시에 전체 합 totalSum도 계산한다.
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        totalSum += arr[i];
    }

    // 전체 합이 홀수면
    // 두 집합의 합을 정확히 같게 나눌 수 없다.
    //
    // 예:
    // totalSum = 15 이면
    // 두 집합 합이 각각 7.5가 되어야 하는데
    // 정수 합으로는 불가능하다.
    if (totalSum % 2 != 0) {
        cout << "불가능하다\n";
        return 0;
    }

    // 목표 합은 전체 합의 절반
    target = totalSum / 2;

    // 백트래킹 시작
    // 처음에는 아직 아무 원소도 결정하지 않았으므로 index = 0
    // A집합의 현재 합도 0이다.
    if (partitionBacktrack(0, 0)) {
        // 성공한 경우
        cout << "가능하다\n";

        // A집합 출력
        cout << "집합 A: ";
        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                cout << arr[i] << ' ';
            }
        }
        cout << '\n';

        // B집합 출력
        cout << "집합 B: ";
        for (int i = 0; i < n; i++) {
            if (!selected[i]) {
                cout << arr[i] << ' ';
            }
        }
        cout << '\n';
    } else {
        // 실패한 경우
        cout << "불가능하다\n";
    }

    return 0;
}

