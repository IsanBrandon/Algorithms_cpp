#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("input1.txt");

/****************************************************************
 * 간선 구조체
 ****************************************************************/
struct Edge {
    int u, v, w;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

/****************************************************************
 * Union-Find
 ****************************************************************/
struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

/****************************************************************
 * Kruskal MST
 ****************************************************************/
long long kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(n);

    long long totalCost = 0;
    int edgeCount = 0;

    for (Edge e : edges) {

        // 사이클이 생기지 않는 경우만 선택
        if (dsu.unite(e.u, e.v)) {

            totalCost += e.w;
            edgeCount++;

            if (edgeCount == n - 1)
                break;
        }
    }

    // MST 구성 실패
    if (edgeCount != n - 1)
        return -1;

    return totalCost;
}

int main() {

    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, m;
    fin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        fin >> edges[i].u
            >> edges[i].v
            >> edges[i].w;
    }

    long long ans = kruskal(n, edges);

    if (ans == -1)
        cout << "IMPOSSIBLE\n";
    else
        cout << ans << "\n";

    fin.close();
}