#include <iostream>
using namespace std;

const int MAXN = 100;

int n, m;
int graph[MAXN][MAXN];
int color[MAXN];

bool promising(int vertex) {
    for (int i = 0; i < vertex; i++) {
        if (graph[vertex][i] == 1 && color[vertex] == color[i]) {
            return false;
        }
    }
    return true;
}

int countColoring(int vertex) {
    if (vertex == n) {
        return 1; // 하나의 완성된 해
    }

    int count = 0;

    for (int c = 1; c <= m; c++) {
        color[vertex] = c;
        if (promising(vertex)) {
            count += countColoring(vertex + 1);
        }
    }

    return count;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }

    cout << countColoring(0) << '\n';

    return 0;
}

