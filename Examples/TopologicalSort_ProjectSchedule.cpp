#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("input1.txt");

/*
 * 위상정렬 함수
 *
 * 반환값:
 * - 사이클이 없으면 위상정렬 순서
 * - 사이클이 있으면 일부 정점만 들어간 불완전한 order 반환
 */
vector<int> topologicalSort(int n, vector<vector<int>> &adj) {
    vector<int> indeg(n, 0);

    // 모든 간선 u -> v에 대해 v의 진입차수 증가
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indeg[v]++;
        }
    }

    queue<int> q;

    // 선행 조건이 없는 정점부터 시작
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order.push_back(u);

        // u를 처리했으므로 u -> v 간선을 제거한다고 생각
        for (int v : adj[u]) {
            indeg[v]--;

            // v의 모든 선행 조건이 사라지면 queue에 삽입
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    return order;
}

int main() {
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<int>> adj(n);

    // 방향 그래프 입력
    // u -> v : u를 먼저 해야 v를 할 수 있음
    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> order = topologicalSort(n, adj);

    // 모든 정점을 처리하지 못했다면 사이클 존재
    if ((int)order.size() != n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << order[i];
        }
        cout << "\n";
    }

    fin.close();

    return 0;
}