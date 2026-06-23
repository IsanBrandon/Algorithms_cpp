#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/*
 * 방향 그래프 입력 함수
 *
 * 입력 형식:
 * n m
 * u1 v1
 * u2 v2
 * ...
 *
 * 의미:
 * u -> v 방향 간선
 */
void inputDirectedGraph(int &n, int &m, vector<vector<int>> &adj) {
    fin >> n >> m;

    // 정점 n개에 대해 빈 인접 리스트 생성
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;

        // 방향 그래프이므로 u의 리스트에만 v를 저장
        adj[u].push_back(v);
    }
}

/*
 * Kahn Algorithm을 이용한 위상정렬
 *
 * 핵심 아이디어:
 * 1. 각 정점의 진입차수 indegree를 계산한다.
 * 2. 진입차수가 0인 정점부터 처리한다.
 * 3. 정점 u를 처리하면 u에서 나가는 간선을 제거한 것처럼
 *    인접 정점 v의 indegree를 1 감소시킨다.
 * 4. indegree가 새롭게 0이 된 정점을 queue에 넣는다.
 */
vector<int> topologicalSort(int n, vector<vector<int>> &adj) {
    vector<int> indeg(n, 0); // 크기가 6인 벡터를 만들고 모든 값을 0으로 초기화하라

    // 모든 간선 u -> v에 대해 v의 진입차수 증가
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indeg[v]++;
        }
    }

    queue<int> q;

    // 처음부터 선행 작업이 없는 정점들을 queue에 삽입
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 현재 정점을 위상정렬 결과에 추가
        order.push_back(u);

        // u -> v 간선을 제거한다고 생각
        for (int v : adj[u]) {
            indeg[v]--;

            // v의 모든 선행 작업이 처리되었다면 queue에 삽입
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
    vector<vector<int>> adj;

    inputDirectedGraph(n, m, adj);

    vector<int> order = topologicalSort(n, adj);

    /*
     * 만약 order의 크기가 n보다 작다면,
     * 모든 정점을 처리하지 못했다는 뜻이다.
     *
     * 즉, 어떤 정점들은 cycle 때문에 indegree가 0이 되지 못했다.
     */
    if ((int)order.size() != n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int x : order) {
            cout << x << " ";
        }
        cout << "\n";
    }

    fin.close();

    return 0;
}