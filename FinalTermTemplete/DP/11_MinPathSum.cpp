#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// 충분히 큰 값
const int INF = 1e9;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * minPathSum
 *
 * 목적:
 * - 행렬의 왼쪽 위 (0,0)에서 오른쪽 아래 (n-1,m-1)까지
 *   이동할 때의 최소 경로합을 구한다.
 *
 * 이동 가능 방향:
 * - 오른쪽
 * - 아래쪽
 *
 * DP 정의:
 * dp[i][j] = (0,0)에서 (i,j)까지 도달하는 최소합
 *
 * 핵심 관찰:
 * (i,j)에 도달하는 직전 칸은 둘 중 하나이다.
 *
 * 1. 위쪽 칸   (i-1,j)
 * 2. 왼쪽 칸   (i,j-1)
 *
 * 따라서:
 * dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1])
 *
 * 단, 첫 행과 첫 열은 예외 처리가 필요하다.
 ***********************************************************************/
int minPathSum(vector<vector<int>> &a) {
    int n = a.size();
    int m = a[0].size();

    /*
     * dp[i][j]:
     * 시작점 (0,0)에서 (i,j)까지 도달하는 최소합
     */
    vector<vector<int>> dp(n, vector<int>(m, INF));

    /*
     * 시작점
     *
     * (0,0)에 도달하는 비용은
     * 그 칸 자체의 값이다.
     */
    dp[0][0] = a[0][0];

    /*
     * 모든 칸을 왼쪽 위부터 오른쪽 아래 방향으로 계산한다.
     *
     * 이유:
     * dp[i][j]는 dp[i-1][j]와 dp[i][j-1]에 의존하기 때문에
     * 위쪽과 왼쪽 값이 먼저 계산되어 있어야 한다.
     */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            /*
             * 위쪽 칸에서 내려오는 경우
             *
             * i > 0일 때만 위쪽 칸이 존재한다.
             */
            if (i > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[i][j]);
            }

            /*
             * 왼쪽 칸에서 오른쪽으로 오는 경우
             *
             * j > 0일 때만 왼쪽 칸이 존재한다.
             */
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + a[i][j]);
            }
        }
    }

    /*
     * 최종 목적지는 오른쪽 아래 칸
     */
    return dp[n - 1][m - 1];
}

int main() {
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, m;

    /*
     * n = 행 개수
     * m = 열 개수
     */
    fin >> n >> m;

    /*
     * 행렬 입력
     */
    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> a[i][j];
        }
    }

    /*
     * 최소 경로합 계산 및 출력
     */
    cout << minPathSum(a) << "\n";

    fin.close();

    return 0;
}