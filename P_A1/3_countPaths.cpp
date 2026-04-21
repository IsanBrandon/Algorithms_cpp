#include <iostream>
using namespace std;

int N, K;
int maze[16][16];
bool visited[16][16];

int countPaths(int x, int y, int remaining) {
    // 범위 밖
    if (x < 0 || y < 0 || x >= N || y >= N) return 0;
    // 벽이거나 이미 방문한 곳
    if (maze[x][y] == 1 || visited[x][y]) return 0; 
    // 이동 회수 초과 
    if (remaining < 0) return 0; 
    // 도착
    if (x == N - 1 && y == N - 1) return 1; 

    visited[x][y] = true;

    int total = 
        countPaths(x - 1, y, remaining - 1) + // 서
        countPaths(x, y + 1, remaining - 1) + // 북
        countPaths(x + 1, y, remaining - 1) + // 동
        countPaths(x, y - 1, remaining - 1);  // 남

    visited[x][y] = false;

    return total;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {for (int j = 0; j < N; j++) cin >> maze[i][j]; }
    cin >> K;

    cout << countPaths(0, 0, K);
    
    return 0;
}


