#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// 도달 불가능을 의미하는 충분히 큰 값
const int INF = 1e9;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Floyd-Warshall Algorithm
 *
 * 목적:
 * - 모든 정점 쌍 (i, j)에 대해
 *   i에서 j까지의 최단거리를 구한다.
 *
 * 핵심 아이디어:
 * - dist[i][j] = 현재까지 알고 있는 i -> j 최단거리
 *
 * k번 정점을 중간 정점으로 사용할 수 있다고 생각할 때,
 *
 * i -> j 로 바로 가는 기존 경로보다
 * i -> k -> j 로 가는 경로가 더 짧으면 갱신한다.
 *
 * 점화식:
 * dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *
 * 시간복잡도:
 * O(n^3)
 ***********************************************************************/
void floydWarshall(vector<vector<int>> &dist) {
    int n = dist.size();

    /*
     * k:
     * 중간 정점으로 사용할 수 있는 정점
     *
     * i:
     * 출발 정점
     *
     * j:
     * 도착 정점
     */
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                /*
                 * i -> k 또는 k -> j 경로가 없다면
                 * i -> k -> j 경로도 만들 수 없다.
                 */
                if (dist[i][k] == INF || dist[k][j] == INF) {
                    continue;
                }

                /*
                 * 기존 i -> j 거리보다
                 * i -> k -> j로 가는 거리가 더 짧으면 갱신
                 */
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    /*******************************************************************
     * input1.txt 파일 열기 확인
     *******************************************************************/
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, m;

    /*
     * 입력:
     * n = 정점 개수
     * m = 간선 개수
     */
    fin >> n >> m;

    /*
     * dist[i][j]:
     * i에서 j까지의 현재 최단거리
     *
     * 처음에는 모든 거리를 INF로 초기화한다.
     */
    vector<vector<int>> dist(n, vector<int>(n, INF));

    /*
     * 자기 자신까지의 거리는 0
     *
     * i -> i 최단거리는 아무 간선도 사용하지 않으면 되므로 0
     */
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    /*
     * 간선 입력
     *
     * u -> v 가중치 w
     *
     * 여러 개의 같은 방향 간선이 있을 수 있으므로
     * 더 작은 가중치를 저장한다.
     */
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;

        dist[u][v] = min(dist[u][v], w);

        // 만약 무방향 그래프라면 아래 줄도 추가한다.
        // dist[v][u] = min(dist[v][u], w);
    }

    /*
     * Floyd-Warshall 수행
     */
    floydWarshall(dist);

    /*
     * 결과 출력
     *
     * dist[i][j] == INF이면
     * i에서 j로 갈 수 없다는 뜻
     */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF";
            } else {
                cout << dist[i][j];
            }

            if (j + 1 < n) cout << " ";
        }
        cout << "\n";
    }

    fin.close();

    return 0;
}