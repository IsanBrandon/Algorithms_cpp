#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("input1.txt");

const int INF = 1e9;

/****************************************************************
 * Dijkstra
 ****************************************************************/
vector<int> dijkstra(
    int n,
    int start,
    vector<vector<pair<int,int>>>& adj)
{
    vector<int> dist(n, INF);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {

        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // 오래된 정보 무시
        if (cost > dist[u])
            continue;

        for (auto edge : adj[u]) {

            int v = edge.first;
            int w = edge.second;

            // 더 짧은 경로 발견
            if (dist[v] > dist[u] + w) {

                dist[v] = dist[u] + w;

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

    fin >> n >> m >> start;

    vector<vector<pair<int,int>>> adj(n);

    for (int i = 0; i < m; i++) {

        int u, v, w;

        fin >> u >> v >> w;

        adj[u].push_back({v, w});
    }

    vector<int> dist =
        dijkstra(n, start, adj);

    for (int d : dist) {

        if (d == INF)
            cout << "INF\n";
        else
            cout << d << "\n";
    }

    fin.close();
}