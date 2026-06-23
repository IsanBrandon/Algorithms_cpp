#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * LCS: Longest Common Subsequence
 *
 * 목적:
 * - 두 문자열 x, y의 최장 공통 부분수열 길이를 구한다.
 *
 * 예:
 * x = ABCBDAB
 * y = BDCABA
 *
 * LCS 길이 = 4
 *
 * DP 정의:
 * dp[i][j] =
 * x의 앞 i글자와 y의 앞 j글자 사이의 LCS 길이
 *
 * 즉:
 * dp[i][j]는
 * x[0 ... i-1] 와 y[0 ... j-1]의 LCS 길이를 의미한다.
 *
 * 핵심 경우:
 *
 * 1. x[i-1] == y[j-1]
 *
 *    두 문자열의 마지막 문자가 같으므로
 *    이 문자를 LCS에 포함할 수 있다.
 *
 *    dp[i][j] = dp[i-1][j-1] + 1
 *
 * 2. x[i-1] != y[j-1]
 *
 *    두 문자를 동시에 사용할 수 없으므로
 *    둘 중 하나를 버린 경우 중 큰 값을 선택한다.
 *
 *    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *
 * 시간복잡도:
 * O(nm)
 ***********************************************************************/
int lcs(string x, string y) {
    int n = x.size();
    int m = y.size();

    /*
     * dp 배열 크기를 (n+1) x (m+1)로 만든다.
     *
     * dp[0][j] = 0
     * dp[i][0] = 0
     *
     * 한쪽 문자열 길이가 0이면
     * 공통 부분수열의 길이는 항상 0이기 때문이다.
     */
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    /*
     * i는 x의 앞 i글자를 의미
     * j는 y의 앞 j글자를 의미
     */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            /*
             * x[i-1]과 y[j-1]을 비교하는 이유:
             *
             * C++ string index는 0부터 시작하고,
             * dp index는 길이를 기준으로 1부터 사용하기 때문.
             */
            if (x[i - 1] == y[j - 1]) {

                // 마지막 문자가 같으므로 LCS 길이 1 증가
                dp[i][j] = dp[i - 1][j - 1] + 1;

            } else {

                // 마지막 문자가 다르면 하나를 버린 두 경우 중 최댓값
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    /*
     * 전체 문자열 x와 y의 LCS 길이
     */
    return dp[n][m];
}

int main() {
    /*******************************************************************
     * input1.txt 파일 열기 확인
     *******************************************************************/
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    string x, y;

    /*
     * 두 문자열 입력
     *
     * 입력 예:
     * ABCBDAB
     * BDCABA
     */
    fin >> x >> y;

    /*
     * LCS 길이 출력
     */
    cout << lcs(x, y) << "\n";

    fin.close();

    return 0;
}