#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
// cin 대신 fin을 사용하면 된다.
ifstream fin("input1.txt");

/*
 * DFS 함수
 *
 * 목적:
 * - 현재 정점 u에서 출발해서 도달 가능한 모든 정점을 방문 표시한다.
 *
 * 매개변수:
 * - u: 현재 방문 중인 정점
 * - adj: 그래프의 인접 리스트
 * - visited: 각 정점의 방문 여부
 */
void dfs(int u, vector<vector<int>> &adj, vector<bool> &visited) {
    // 현재 정점 u를 방문했다고 표시
    visited[u] = true;

    // u와 연결된 모든 이웃 정점 v를 확인
    for (int v : adj[u]) {
        // 아직 방문하지 않은 정점이면 재귀적으로 방문
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

/*
 * 무방향 그래프 입력 함수
 *
 * input1.txt 형식:
 * n m
 * u1 v1
 * u2 v2
 * ...
 * um vm
 *
 * n: 정점 개수
 * m: 간선 개수
 * u v: u와 v 사이에 무방향 간선이 존재
 */
void inputUndirectedGraph(int &n, int &m, vector<vector<int>> &adj) {
    // 정점 수 n, 간선 수 m 입력
    fin >> n >> m;

    // 정점이 n개이므로 adj[0] ~ adj[n-1]까지 생성
    // adj[i]에는 정점 i와 연결된 정점들이 저장된다.
    adj.assign(n, vector<int>());

    // 간선 m개 입력
    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;

        // 무방향 그래프이므로 양쪽 모두에 저장해야 한다.
        // u와 v가 연결됨
        adj[u].push_back(v);

        // v와 u도 연결됨
        adj[v].push_back(u);
    }
}

/*
 * 트리 판정 함수
 *
 * 무방향 그래프가 트리이려면:
 * 1. 간선 수가 n - 1개여야 한다.
 * 2. 모든 정점이 하나로 연결되어 있어야 한다.
 *
 * 즉:
 * m == n - 1 && connected
 */
bool isTree(int n, int m, vector<vector<int>> &adj) {
    // 트리의 기본 성질:
    // 정점이 n개인 트리는 반드시 간선이 n-1개이다.
    // 따라서 이 조건을 만족하지 않으면 바로 트리가 아니다.
    if (m != n - 1) return false;

    // 연결성 검사를 위한 방문 배열
    vector<bool> visited(n, false);

    // 0번 정점에서 DFS 시작
    // 그래프가 연결되어 있다면 DFS 한 번으로 모든 정점을 방문할 수 있다.
    dfs(0, adj, visited);

    // DFS 후 방문하지 못한 정점이 하나라도 있으면
    // 그래프가 disconnected라는 뜻이므로 트리가 아니다.
    for (int i = 0; i < n; i++) {
        if (!visited[i]) return false;
    }

    // 간선 수가 n-1이고 모든 정점이 연결되어 있으므로 트리이다.
    return true;
}

int main() {
    // input1.txt 파일이 제대로 열렸는지 확인
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, m;
    vector<vector<int>> adj;

    // input1.txt에서 무방향 그래프 입력
    inputUndirectedGraph(n, m, adj);

    // 트리인지 판정 후 결과 출력
    if (isTree(n, m, adj)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    // 파일 닫기
    fin.close();

    return 0;
}