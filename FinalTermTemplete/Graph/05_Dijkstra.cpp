#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// 충분히 큰 값.
// 아직 도달하지 못한 정점의 거리를 INF로 둔다.
const int INF = 1e9;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Dijkstra Algorithm
 *
 * 목적:
 * - 시작 정점 start에서 모든 정점까지의 최단거리를 구한다.
 *
 * 조건:
 * - 간선 가중치가 음수가 아니어야 한다.
 *
 * 입력:
 * - n     : 정점 개수
 * - start : 시작 정점
 * - adj   : 인접 리스트
 *
 * adj[u]에는 {v, w}가 저장된다.
 * 의미: u -> v 방향 간선이 있고, 그 가중치는 w이다.
 *
 * 반환:
 * - dist[i] = start에서 i까지의 최단거리
 * - 도달 불가능하면 dist[i] = INF
 ***********************************************************************/
vector<int> dijkstra(int n, int start, vector<vector<pair<int, int>>> &adj) {
    /*
     * dist[i]:
     * start에서 정점 i까지 현재까지 발견된 최단거리
     *
     * 처음에는 모든 정점에 도달하지 못했다고 보고 INF로 초기화한다.
     */
    vector<int> dist(n, INF);

    /*
     * 우선순위 큐
     *
     * 저장 형식:
     * {거리, 정점}
     *
     * priority_queue는 기본적으로 큰 값이 먼저 나오므로,
     * greater<pair<int,int>>를 사용해서
     * 거리가 가장 작은 정점이 먼저 나오게 만든다.
     */
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    // 시작 정점까지의 거리는 0
    dist[start] = 0;

    // 시작 정점을 우선순위 큐에 삽입
    pq.push({0, start});

    while (!pq.empty()) {
        /*
         * 현재 가장 거리가 짧은 후보 정점을 꺼낸다.
         */
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        /*
         * 이미 더 짧은 경로가 나중에 발견된 경우,
         * 이 정보는 오래된 정보이므로 무시한다.
         *
         * 예:
         * pq에는 {10, 3}이 들어 있었는데,
         * 나중에 dist[3] = 5가 되었다면
         * {10, 3}은 더 이상 쓸 필요가 없다.
         */
        if (cost > dist[u]) {
            continue;
        }

        /*
         * u에서 갈 수 있는 모든 정점 v를 확인한다.
         */
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            /*
             * Relaxation
             *
             * 기존에 알고 있던 start -> v 거리보다
             * start -> u -> v 로 가는 거리가 더 짧다면 갱신한다.
             */
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;

                // 갱신된 정보를 우선순위 큐에 삽입
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, m, start;

    /*
     * 입력:
     * n = 정점 개수
     * m = 간선 개수
     * start = 시작 정점
     */
    fin >> n >> m >> start;

    /*
     * 가중치 방향 그래프 인접 리스트
     *
     * adj[u] = u에서 나가는 간선들의 목록
     * 각 원소는 {v, w}
     *
     * 의미:
     * u -> v, 가중치 w
     */
    vector<vector<pair<int, int>>> adj(n);

    /*
     * 간선 입력
     */
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;

        // 방향 그래프이므로 u -> v만 저장
        adj[u].push_back({v, w});

        // 만약 무방향 그래프라면 아래 줄도 추가한다.
        // adj[v].push_back({u, w});
    }

    /*
     * Dijkstra 수행
     */
    vector<int> dist = dijkstra(n, start, adj);

    /*
     * 결과 출력
     *
     * 각 정점 i에 대해 start에서 i까지의 최단거리 출력
     * 도달할 수 없는 경우 INF 출력 대신 "INF" 문자열 출력
     */
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            cout << "INF\n";
        } else {
            cout << dist[i] << "\n";
        }
    }

    fin.close();

    return 0;
}