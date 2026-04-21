#include <iostream>   // cin, cout
#include <cmath>      // sqrt
#include <iomanip>    // setprecision
using namespace std;

// 정점(점)의 최대 개수
const int MAXN = 20;

// 충분히 큰 값 (최소값 비교를 위한 초기값)
const double INF = 1e18;

// 점의 개수
int n;

// 각 점의 x좌표, y좌표
double x[MAXN], y[MAXN];

// distArr[i][j] = i번 점에서 j번 점까지의 거리
double distArr[MAXN][MAXN];

// 현재 백트래킹 중인 경로
// path[0], path[1], ..., path[n-1]
int path[MAXN];

// 지금까지 찾은 최적(최소 거리) 경로 저장
int bestPath[MAXN];

// 각 정점의 방문 여부
// visited[i] == true 이면 이미 경로에 포함된 정점
bool visited[MAXN];

// 지금까지 찾은 최소 순회 길이
double bestLength = INF;


// ------------------------------------------------------------
// getDistance(i, j)
// ------------------------------------------------------------
// i번 점과 j번 점 사이의 유클리드 거리를 계산하는 함수
//
// 거리 공식:
//   sqrt( (x_i - x_j)^2 + (y_i - y_j)^2 )
// ------------------------------------------------------------
double getDistance(int i, int j) {
    double dx = x[i] - x[j];              // x좌표 차이
    double dy = y[i] - y[j];              // y좌표 차이
    return sqrt(dx * dx + dy * dy);       // 유클리드 거리 반환
}


// ------------------------------------------------------------
// tsp(level, currentLength)
// ------------------------------------------------------------
// 의미:
//   현재 path[0] ~ path[level-1] 까지 방문 순서가 정해져 있고,
//   그때까지의 누적 거리 합이 currentLength일 때,
//   남은 정점들을 이어 붙여 최단 Hamiltonian cycle을 찾는다.
//
// 매개변수:
//   level         : 현재까지 path에 채워진 정점 개수
//                   예: level = 1 이면 path[0]만 채워진 상태
//   currentLength : 지금까지 만들어진 경로의 길이 합
//
// 예:
//   path = [0, 3, 2] 이고 level = 3 이면
//   0 -> 3 -> 2 까지 경로가 정해진 상태
//   currentLength는 dist(0,3) + dist(3,2)
//
// 동작:
//   1) 현재 길이가 이미 bestLength 이상이면 가지치기
//   2) 모든 정점을 다 방문했으면 마지막 정점에서 출발점으로 돌아감
//   3) 아직 방문하지 않은 정점 중 하나를 다음 정점으로 선택
//   4) 재귀 호출 후 visited를 복구 (백트래킹)
// ------------------------------------------------------------
void tsp(int level, double currentLength) {

    // [가지치기]
    // 현재까지 누적 거리만 해도 이미 기존 최적해(bestLength) 이상이면
    // 앞으로 더 가도 절대로 더 짧아질 수 없다.
    if (currentLength >= bestLength) {
        return;
    }

    // [기저 조건]
    // 모든 정점을 다 방문한 경우
    if (level == n) {
        // 마지막 정점(path[n-1])에서 출발점(path[0])으로 돌아가야
        // 하나의 완전한 TSP 순회(cycle)가 된다.
        double totalLength = currentLength + distArr[path[level - 1]][path[0]];

        // 더 짧은 경로를 찾았다면 최적해 갱신
        if (totalLength < bestLength) {
            bestLength = totalLength;

            // 현재 경로를 최적 경로로 복사
            for (int i = 0; i < n; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    // [재귀 단계]
    // 아직 방문하지 않은 정점을 다음 방문 정점으로 하나씩 시도
    //
    // 출발점은 path[0] = 0 으로 이미 고정했으므로
    // next는 1번부터 n-1번까지만 보면 된다.
    for (int next = 1; next < n; next++) {

        // 아직 방문하지 않은 정점만 후보가 될 수 있다.
        if (!visited[next]) {

            // next 정점을 현재 경로에 포함
            visited[next] = true;
            path[level] = next;

            // 이전 정점(path[level-1])에서 next로 이동하는 거리를 더해서
            // 다음 단계로 재귀 호출
            tsp(level + 1, currentLength + distArr[path[level - 1]][next]);

            // [백트래킹]
            // 방금 선택했던 next를 다시 미방문 상태로 되돌린다.
            // 그래야 다음 후보 정점도 시도할 수 있다.
            visited[next] = false;
        }
    }
}


int main() {
    // 점의 개수 입력
    cin >> n;

    // 각 점의 좌표 입력
    // 예: n=4 이면 (x0,y0), (x1,y1), (x2,y2), (x3,y3)
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // 모든 점 쌍에 대해 거리 행렬을 미리 계산
    // distArr[i][j] = i번 점에서 j번 점까지의 거리
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distArr[i][j] = getDistance(i, j);
        }
    }

    // 방문 배열 초기화
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // 출발점을 0번으로 고정
    //
    // TSP 순회는 cycle이므로 시작점을 회전시켜도 같은 순회다.
    // 따라서 출발점을 하나 고정해도 최적해를 잃지 않으면서
    // 중복 탐색을 줄일 수 있다.
    path[0] = 0;
    visited[0] = true;

    // 백트래킹 시작
    //
    // 현재 path에는 출발점 0만 들어있으므로 level = 1
    // 아직 이동한 적은 없으므로 currentLength = 0.0
    tsp(1, 0.0);

    // 결과 출력 형식 설정
    cout << fixed << setprecision(6);

    // 최소 순회 길이 출력
    cout << "최소 순회 길이: " << bestLength << '\n';

    // 최적 경로 출력
    //
    // 예: 0 -> 2 -> 1 -> 3 -> 0
    // 마지막에 다시 출발점(bestPath[0])으로 돌아가는 것도 출력
    cout << "최적 경로: ";
    for (int i = 0; i < n; i++) {
        cout << bestPath[i] << " -> ";
    }
    cout << bestPath[0] << '\n';

    return 0;
}