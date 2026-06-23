#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("input1.txt");

/***********************************************************************
 * Edge 구조체
 *
 * 하나의 간선을 표현한다.
 *
 * u: 한쪽 정점
 * v: 다른 쪽 정점
 * w: 간선의 가중치
 ***********************************************************************/
struct Edge {
    int u, v, w;

    // sort(edges.begin(), edges.end())를 했을 때
    // 가중치 w를 기준으로 오름차순 정렬되도록 정의
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

/***********************************************************************
 * DSU, Union-Find
 *
 * Kruskal 알고리즘에서 사이클이 생기는지 판정하기 위해 사용한다.
 *
 * 핵심 기능:
 * 1. find(x): x가 속한 집합의 대표를 찾는다.
 * 2. unite(a, b): a와 b가 속한 두 집합을 합친다.
 *
 * 만약 a와 b가 이미 같은 집합이면,
 * a-b 간선을 추가할 경우 사이클이 생긴다.
 ***********************************************************************/
struct DSU {
    vector<int> parent; // parent[x] = x의 부모
    vector<int> sz;     // sz[x] = x가 대표인 집합의 크기

    // 정점이 n개일 때 DSU 초기화
    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        // 처음에는 모든 정점이 자기 자신만 포함하는 집합
        // 즉 parent[i] = i
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    /*
     * find(x)
     *
     * x가 속한 집합의 대표 노드를 찾는다.
     *
     * parent[x] == x이면 x가 대표이다.
     *
     * path compression:
     * find를 수행하면서 지나간 노드들이 바로 대표를 가리키게 만든다.
     */    
    int find(int x) {
        if (parent[x] == x) return x;

        return parent[x] = find(parent[x]);
    }

    /*
     * unite(a, b)
     *
     * a와 b가 속한 집합을 합친다.
     *
     * 반환값:
     * true  = 서로 다른 집합이었고, 합치기에 성공
     * false = 이미 같은 집합이었음, 즉 이 간선을 추가하면 사이클 발생
     */
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        // 대표가 같으면 이미 같은 집합
        // 이 간선을 선택하면 사이클이 생기므로 선택하지 않음
        if (a == b) return false;

        // 작은 집합을 큰 집합 밑에 붙인다.
        // 트리가 너무 길어지는 것을 방지하기 위함
        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

/***********************************************************************
 * Kruskal MST
 *
 * 입력:
 * n     : 정점 개수
 * edges : 간선 목록
 *
 * 출력:
 * MST의 총 가중치
 * 단, 모든 정점을 연결할 수 없으면 -1 반환
 *
 * 알고리즘:
 * 1. 간선을 가중치 오름차순으로 정렬한다.
 * 2. 작은 간선부터 하나씩 확인한다.
 * 3. 두 정점이 서로 다른 집합이면 선택한다.
 * 4. 두 정점이 이미 같은 집합이면 선택하지 않는다.
 * 5. 선택한 간선 수가 n-1개가 되면 MST 완성.
 ***********************************************************************/
int kruskal(int n, vector<Edge> &edges) {
    // 간선을 가중치 기준 오름차순 정렬
    sort(edges.begin(), edges.end());

    DSU dsu(n);

    int total = 0;  // 선택한 간선들의 가중치 합
    int cnt = 0;    // 선택한 간선 개수

    for (Edge e : edges) {
        /*
         * unite(e.u, e.v)가 true라는 것은
         * e.u와 e.v가 아직 서로 다른 연결요소에 있었다는 뜻.
         *
         * 따라서 이 간선을 선택해도 사이클이 생기지 않는다.
         */
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            cnt++;

            // 정점 n개를 연결하는 트리는 간선 n-1개를 가진다.
            if (cnt == n - 1) break;
        }
    }

    // n-1개의 간선을 선택하지 못했다면
    // 그래프가 disconnected라서 MST를 만들 수 없다.
    if (cnt != n - 1) return -1; // MST 없음

    return total;
}

int main() {
    int n, m;
    fin >> n >> m;

    vector<Edge> edges(m);

    // 간선 정보 입력
    // 각 간선은 u, v, w 형태
    // 무방향 간선이지만 Kruskal에서는 Edge 하나만 저장해도 충분하다.
    for (int i = 0; i < m; i++) {
        fin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // MST 총 가중치 계산
    int result = kruskal(n, edges);
    
    cout << result << endl;

    return 0;
}