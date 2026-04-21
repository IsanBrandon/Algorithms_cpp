#include <iostream>
using namespace std;

const int INF = 1000000000;

int N, K;
int maze[20][20];
int visited[20][20];
int answer = INF; 

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int x, int y, int rest) {
    if (rest >= answer) return;
    
    if (x == N - 1 && y == N - 1) { answer = rest; return; }
    
    visited[x][y] = true;

    for (int dir = 0; dir < 4; dir++) {
        for (int step = 1; step <= K; step++) {
            int nx = x + dx[dir] * step; int ny = y + dy[dir] * step;

            if (nx < 0 || ny < 0 || nx >= N || ny >= N) break;

            if (maze[nx][ny] == 1) break;

            if (visited[nx][ny]) continue;

            dfs(nx, ny, rest + 1);
        }
    }

    visited[x][y] = false;
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

    if (maze[0][0] == 1 || maze[N - 1][N - 1] == 1) { 
        cout << -1 << '\n'; 
        return 0; 
    }

    dfs(0, 0, 0);

    if (answer == INF) cout << -1 << '\n';
    else cout << answer << '\n';

    return 0;
}


