#include <iostream>
using namespace std;

int N, K;
int maze[20][20];
bool visited[20][20];

bool canEscape(int x, int y, int injury) {
    // 1. 범위 밖
    if (x < 0 || y < 0 || x >= N || y >= N) return false;
    // 2. 벽이거나 이미 방문한 곳
    if (maze[x][y] == 1 || visited[x][y]) return false; 
    // 3. 부상 횟수 증가
    if (maze[x][y] == 2) injury++; 
    // 4. 부상 횟수가 K 초과면 죽음
    if (injury > K) return false;
    // 5. 도착점 도달 
    if (x == N - 1 && y == N - 1) return true; 
    
    visited[x][y] = true;   // 방문 표시 

    bool found = 
        canEscape(x - 1, y, injury) + // 위
        canEscape(x + 1, y, injury) + // 아래
        canEscape(x, y - 1, injury) + // 왼쪽
        canEscape(x, y + 1, injury);  // 오른쪽 

    visited[x][y] = false;  // 백트래킹 

    return found;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) { 
            cin >> maze[i][j]; 
            visited[i][j] = false; 
        }
    }
    cin >> K;

    if (canEscape(0, 0, 0)) cout << "Yes\n";
    else cout << "No\n";
    
    return 0;
}


