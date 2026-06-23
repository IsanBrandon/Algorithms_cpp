/* 핵심 기말고사 대비 문제들
00_PA_Template.cpp
01_DFS_TreeCheck.cpp
02_DFS_DirectedCycle.cpp
03_TopologicalSort.cpp
04_KruskalMST.cpp
05_Dijkstra.cpp

11_MinPathSum.cpp
12_MaxSubarray.cpp
13_LCS.cpp
14_Knapsack.cpp
 */

/***********************************************************************
 * Algorithm Final Exam C++ Template
 *
 * 입력 파일 이름: input1.txt
 *
 * 사용법:
 * 1. 필요한 알고리즘 함수는 아래에서 그대로 사용한다.
 * 2. main() 아래의 "입력 형식별 템플릿" 중 문제에 맞는 부분만 복사한다.
 * 3. cin 대신 fin을 사용한다.
 ***********************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <utility>
#include <climits>
#include <cmath>
using namespace std;

const int INF = 1e9;
const long long LINF = 4e18;

/***********************************************************************
 * 0. input1.txt 파일 입력 기본형
 ***********************************************************************/

ifstream fin("input1.txt");

/***********************************************************************
 * 1. 그래프 입력 템플릿
 ***********************************************************************/

// [1-1] 인접행렬 입력
// input:
// n
// n x n matrix
void inputAdjMatrix(int &n, vector<vector<int>> &adj) {
    fin >> n;
    adj.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> adj[i][j];
        }
    }
}

// [1-2] 무방향 그래프 입력
// input:
// n m
// u v
// u v ...
void inputUndirectedGraph(int &n, int &m, vector<vector<int>> &adj) {
    fin >> n >> m;
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// [1-3] 방향 그래프 입력
void inputDirectedGraph(int &n, int &m, vector<vector<int>> &adj) {
    fin >> n >> m;
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;

        adj[u].push_back(v);
    }
}

// [1-4] 가중치 그래프 입력
void inputWeightedGraph(int &n, int &m, vector<vector<pair<int,int>>> &adj, bool undirected) {
    fin >> n >> m;
    adj.assign(n, vector<pair<int,int>>());

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;

        adj[u].push_back({v, w});

        if (undirected) {
            adj[v].push_back({u, w});
        }
    }
}

/***********************************************************************
 * 2. BFS
 * - 무가중치 그래프 최단거리
 * - 연결성 검사
 ***********************************************************************/

vector<int> bfs(int start, vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}

/***********************************************************************
 * 3. DFS 기본형
 ***********************************************************************/

void dfs(int u, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

/***********************************************************************
 * 4. 연결 요소 개수
 ***********************************************************************/

int countComponents(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited);
            cnt++;
        }
    }

    return cnt;
}

/***********************************************************************
 * 5. 무방향 그래프가 트리인지 판정
 *
 * 트리 조건:
 * 1. connected
 * 2. edge 개수 = n - 1
 ***********************************************************************/

bool isTree(int n, int m, vector<vector<int>> &adj) {
    if (m != n - 1) return false;

    vector<bool> visited(n, false);
    dfs(0, adj, visited);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) return false;
    }

    return true;
}

/***********************************************************************
 * 6. 무방향 그래프 사이클 판정
 ***********************************************************************/

bool hasCycleUndirectedDFS(int u, int parent,
                           vector<vector<int>> &adj,
                           vector<bool> &visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (hasCycleUndirectedDFS(v, u, adj, visited))
                return true;
        }
        else if (v != parent) {
            return true;
        }
    }

    return false;
}

bool hasCycleUndirected(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (hasCycleUndirectedDFS(i, -1, adj, visited))
                return true;
        }
    }

    return false;
}

/***********************************************************************
 * 7. 방향 그래프 사이클 판정
 *
 * color:
 * 0 = unvisited
 * 1 = visiting / gray
 * 2 = finished / black
 ***********************************************************************/

bool dfsCycleDirected(int u, vector<vector<int>> &adj, vector<int> &color) {
    color[u] = 1;

    for (int v : adj[u]) {
        if (color[v] == 1) return true;

        if (color[v] == 0) {
            if (dfsCycleDirected(v, adj, color))
                return true;
        }
    }

    color[u] = 2;
    return false;
}

bool hasCycleDirected(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> color(n, 0);

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (dfsCycleDirected(i, adj, color))
                return true;
        }
    }

    return false;
}

/***********************************************************************
 * 8. 위상정렬: Kahn Algorithm
 *
 * DAG이면 order.size() == n
 * cycle이 있으면 order.size() < n
 ***********************************************************************/

vector<int> topologicalSort(int n, vector<vector<int>> &adj) {
    vector<int> indeg(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indeg[v]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order.push_back(u);

        for (int v : adj[u]) {
            indeg[v]--;

            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    return order;
}

/***********************************************************************
 * 9. Union-Find / Disjoint Set
 ***********************************************************************/

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

/***********************************************************************
 * 10. Kruskal MST
 ***********************************************************************/

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

int kruskal(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    int total = 0;
    int cnt = 0;

    for (Edge e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            cnt++;

            if (cnt == n - 1) break;
        }
    }

    if (cnt != n - 1) return -1; // MST 없음

    return total;
}

/***********************************************************************
 * 11. Dijkstra
 *
 * 조건:
 * - 음수 가중치 없음
 ***********************************************************************/

vector<int> dijkstra(int n, int start, vector<vector<pair<int,int>>> &adj) {
    vector<int> dist(n, INF);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (cost > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

/***********************************************************************
 * 12. Floyd-Warshall
 *
 * 모든 정점 쌍 최단거리
 * 시간복잡도: O(n^3)
 ***********************************************************************/

void floydWarshall(vector<vector<int>> &dist) {
    int n = dist.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

/***********************************************************************
 * 13. 행렬 최소 경로합 DP
 *
 * 이동 가능:
 * - 오른쪽
 * - 아래쪽
 ***********************************************************************/

int minPathSum(vector<vector<int>> &a) {
    int n = a.size();
    int m = a[0].size();

    vector<vector<int>> dp(n, vector<int>(m, INF));

    dp[0][0] = a[0][0];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[i][j]);
            }

            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + a[i][j]);
            }
        }
    }

    return dp[n - 1][m - 1];
}

/***********************************************************************
 * 14. LCS 길이
 ***********************************************************************/

int lcs(string x, string y) {
    int n = x.size();
    int m = y.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

/***********************************************************************
 * 15. 최대 연속 부분합
 ***********************************************************************/

// 아무것도 선택하지 않는 경우 허용
int maxSubarraySum(vector<int> &a) {
    int cur = 0;
    int best = 0;

    for (int x : a) {
        cur = max(0, cur + x);
        best = max(best, cur);
    }

    return best;
}

// 반드시 하나 이상 선택
int maxSubarraySumNonEmpty(vector<int> &a) {
    int cur = a[0];
    int best = a[0];

    for (int i = 1; i < (int)a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }

    return best;
}

/***********************************************************************
 * 16. 0/1 Knapsack
 ***********************************************************************/

int knapsack(vector<int> &w, vector<int> &v, int W) {
    int n = w.size();

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int cap = 0; cap <= W; cap++) {
            dp[i][cap] = dp[i - 1][cap];

            if (cap >= w[i - 1]) {
                dp[i][cap] = max(
                    dp[i][cap],
                    dp[i - 1][cap - w[i - 1]] + v[i - 1]
                );
            }
        }
    }

    return dp[n][W];
}

/***********************************************************************
 * 17. 이항계수 DP
 ***********************************************************************/

long long binomial(int n, int k) {
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }

    return dp[n][k];
}

/***********************************************************************
 * 18. Hash / 빈도수 세기
 ***********************************************************************/

void countStringFrequency() {
    int n;
    fin >> n;

    unordered_map<string, int> freq;

    for (int i = 0; i < n; i++) {
        string s;
        fin >> s;
        freq[s]++;
    }

    for (auto [key, value] : freq) {
        cout << key << " " << value << "\n";
    }
}

/***********************************************************************
 * 19. Sliding Window + Hash
 *
 * 길이 k인 모든 구간에서 서로 다른 원소 개수 구하기
 ***********************************************************************/

vector<int> distinctInWindow(vector<int> &a, int k) {
    unordered_map<int, int> cnt;
    vector<int> ans;

    for (int i = 0; i < (int)a.size(); i++) {
        cnt[a[i]]++;

        if (i >= k) {
            cnt[a[i - k]]--;

            if (cnt[a[i - k]] == 0) {
                cnt.erase(a[i - k]);
            }
        }

        if (i >= k - 1) {
            ans.push_back(cnt.size());
        }
    }

    return ans;
}

/***********************************************************************
 * 20. BST 기본 구현
 ***********************************************************************/

struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int key) {
        this->key = key;
        left = nullptr;
        right = nullptr;
    }
};

Node* insertBST(Node *root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insertBST(root->left, key);
    }
    else {
        root->right = insertBST(root->right, key);
    }

    return root;
}

bool searchBST(Node *root, int key) {
    if (root == nullptr) return false;
    if (root->key == key) return true;

    if (key < root->key) {
        return searchBST(root->left, key);
    }
    else {
        return searchBST(root->right, key);
    }
}

void inorderBST(Node *root) {
    if (root == nullptr) return;

    inorderBST(root->left);
    cout << root->key << "\n";
    inorderBST(root->right);
}

int heightBST(Node *root) {
    if (root == nullptr) return -1;

    return 1 + max(heightBST(root->left), heightBST(root->right));
}

/***********************************************************************
 * 21. CCW / Convex Hull 대비
 ***********************************************************************/

struct Point {
    long long x, y;
};

long long ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

/***********************************************************************
 * 22. 날짜 입력 / 정렬 대비
 ***********************************************************************/

int monthNumber(string m) {
    if (m == "Jan") return 1;
    if (m == "Feb") return 2;
    if (m == "Mar") return 3;
    if (m == "Apr") return 4;
    if (m == "May") return 5;
    if (m == "Jun") return 6;
    if (m == "Jul") return 7;
    if (m == "Aug") return 8;
    if (m == "Sep") return 9;
    if (m == "Oct") return 10;
    if (m == "Nov") return 11;
    if (m == "Dec") return 12;

    return 0;
}

struct Date {
    string monStr;
    int month;
    int day;
    int year;
};

bool dateLess(Date a, Date b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;

    return a.day < b.day;
}

/***********************************************************************
 * 23. 입력 형식별 main 템플릿
 *
 * 시험장에서 아래 예시 중 하나를 골라 main() 안에 넣으면 된다.
 ***********************************************************************/

int main() {
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    /*******************************************************************
     * [A] 인접행렬 그래프 입력 예시
     *
     * input1.txt:
     * n
     * 0 1 1 ...
     * 1 0 0 ...
     *******************************************************************/
    /*
    int n;
    vector<vector<int>> adjMatrix;

    inputAdjMatrix(n, adjMatrix);

    cout << "n = " << n << "\n";
    */

    /*******************************************************************
     * [B] 무방향 그래프 입력 + 트리 판정
     *
     * input1.txt:
     * n m
     * u v
     * u v
     *******************************************************************/
    /*
    int n, m;
    vector<vector<int>> adj;

    inputUndirectedGraph(n, m, adj);

    if (isTree(n, m, adj)) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
    */

    /*******************************************************************
     * [C] 방향 그래프 입력 + 사이클 판정
     *******************************************************************/
    /*
    int n, m;
    vector<vector<int>> adj;

    inputDirectedGraph(n, m, adj);

    if (hasCycleDirected(adj)) {
        cout << "Cycle exists\n";
    }
    else {
        cout << "No cycle\n";
    }
    */

    /*******************************************************************
     * [D] DAG 위상정렬
     *******************************************************************/
    /*
    int n, m;
    vector<vector<int>> adj;

    inputDirectedGraph(n, m, adj);

    vector<int> order = topologicalSort(n, adj);

    if ((int)order.size() != n) {
        cout << "Cycle exists\n";
    }
    else {
        for (int x : order) {
            cout << x << " ";
        }
        cout << "\n";
    }
    */

    /*******************************************************************
     * [E] Kruskal MST 입력
     *
     * input1.txt:
     * n m
     * u v w
     * u v w
     *******************************************************************/
    /*
    int n, m;
    fin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    cout << kruskal(n, edges) << "\n";
    */

    /*******************************************************************
     * [F] Dijkstra 입력
     *******************************************************************/
    /*
    int n, m, start;
    fin >> n >> m >> start;

    vector<vector<pair<int,int>>> adj;
    adj.assign(n, vector<pair<int,int>>());

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;

        adj[u].push_back({v, w});
        // 무방향 그래프면 아래 추가
        // adj[v].push_back({u, w});
    }

    vector<int> dist = dijkstra(n, start, adj);

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }
    */

    /*******************************************************************
     * [G] Floyd-Warshall 입력
     *******************************************************************/
    /*
    int n, m;
    fin >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;

        dist[u][v] = min(dist[u][v], w);
        // 무방향이면 아래 추가
        // dist[v][u] = min(dist[v][u], w);
    }

    floydWarshall(dist);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    */

    /*******************************************************************
     * [H] n x n 행렬 DP 입력
     *******************************************************************/
    /*
    int n;
    fin >> n;

    vector<vector<int>> a(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> a[i][j];
        }
    }

    cout << minPathSum(a) << "\n";
    */

    /*******************************************************************
     * [I] 배열 입력 + 최대 연속 부분합
     *******************************************************************/
    /*
    int n;
    fin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    cout << maxSubarraySum(a) << "\n";
    */

    /*******************************************************************
     * [J] 문자열 2개 입력 + LCS
     *******************************************************************/
    /*
    string x, y;
    fin >> x >> y;

    cout << lcs(x, y) << "\n";
    */

    /*******************************************************************
     * [K] Knapsack 입력
     *
     * input1.txt:
     * n W
     * w1 v1
     * w2 v2
     *******************************************************************/
    /*
    int n, W;
    fin >> n >> W;

    vector<int> w(n), v(n);

    for (int i = 0; i < n; i++) {
        fin >> w[i] >> v[i];
    }

    cout << knapsack(w, v, W) << "\n";
    */

    /*******************************************************************
     * [L] 날짜 입력
     *
     * input1.txt:
     * n
     * Feb 19, 2024
     * Jan 4, 2022
     *******************************************************************/
    /*
    int n;
    fin >> n;

    vector<Date> dates;

    for (int i = 0; i < n; i++) {
        string mon;
        int day, year;
        char comma;

        fin >> mon >> day >> comma >> year;

        dates.push_back({mon, monthNumber(mon), day, year});
    }

    sort(dates.begin(), dates.end(), dateLess);

    for (Date d : dates) {
        cout << d.monStr << " " << d.day << ", " << d.year << "\n";
    }
    */

    /*******************************************************************
     * [M] 공백 포함 한 줄 입력
     *******************************************************************/
    /*
    int n;
    fin >> n;
    fin.ignore();

    for (int i = 0; i < n; i++) {
        string line;
        getline(fin, line);

        cout << line << "\n";
    }
    */

    fin.close();

    return 0;
}