#include <iostream>
using namespace std;

const int MAXN = 100;   // 정점 최대 개수 (필요하면 더 크게 조정 가능)

int n;                  // 정점의 개수
int m;                  // 사용할 색의 개수
int graph[MAXN][MAXN];  // 인접행렬: graph[i][j] == 1 이면 i와 j가 인접
int color[MAXN];        // color[i] = i번 정점에 칠한 색 (1 ~ m)

// vertex번 정점에 현재 칠한 색이 이전 정점들과 충돌하지 않는지 검사
bool promising(int vertex) {
    for (int i = 0; i < vertex; i++) {
        // i번 정점과 vertex번 정점이 인접하고, 색까지 같으면 실패
        if (graph[vertex][i] == 1 && color[vertex] == color[i]) {
            return false;
        }
    }
    return true;
}

// vertex번 정점까지 색칠을 진행하는 백트래킹 함수
bool mColoring(int vertex) {
    // 모든 정점을 다 색칠했으면 성공
    if (vertex == n) {
        return true;
    }

    // 현재 vertex번 정점에 대해 1 ~ m 색을 하나씩 시도
    for (int c = 1; c <= m; c++) {
        color[vertex] = c;   // 색 하나를 가정해서 칠함

        // 현재 선택이 유망하면 다음 정점으로 진행
        if (promising(vertex)) {
            if (mColoring(vertex + 1)) {
                return true; // 하나라도 성공하면 전체 성공
            }
        }

        // 실패하면 다음 색을 시도
        // color[vertex]는 다음 반복에서 덮어써지므로 따로 초기화하지 않아도 됨
    }

    // 가능한 모든 색을 시도했는데도 안 되면 실패
    return false;
}

int main() {
    cin >> n >> m;

    // 인접행렬 입력
    // 예: n x n 형태로 0 또는 1 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    // 색 배열 초기화
    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }

    // 0번 정점부터 색칠 시작
    if (mColoring(0)) {
        cout << "가능하다\n";
        cout << "한 가지 색칠 결과:\n";
        for (int i = 0; i < n; i++) {
            cout << "정점 " << i << " -> 색 " << color[i] << '\n';
        }
    } else {
        cout << "불가능하다\n";
    }

    return 0;
}


