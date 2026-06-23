#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

ifstream fin("input1.txt");

/*****************************************************************
 * LCS
 *
 * dp[i][j]
 *
 * = 문자열 A의 앞 i개
 *   문자열 B의 앞 j개
 *
 * 사이의 LCS 길이
 *
 * 점화식
 *
 * 같으면
 *
 * dp[i][j]
 * =
 * dp[i-1][j-1] + 1
 *
 * 다르면
 *
 * dp[i][j]
 * =
 * max(
 *   dp[i-1][j],
 *   dp[i][j-1]
 * )
 *****************************************************************/
int LCS(string A, string B) {

    int n = A.size();
    int m = B.size();

    vector<vector<int>> dp(
        n + 1,
        vector<int>(m + 1, 0)
    );

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            // 현재 문자 동일
            if (A[i - 1] == B[j - 1]) {

                dp[i][j]
                =
                dp[i - 1][j - 1]
                + 1;
            }

            // 현재 문자 다름
            else {

                dp[i][j]
                =
                max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    return dp[n][m];
}

int main() {

    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    string A, B;

    fin >> A >> B;

    /*************************************************************
     * 공통 부분수열 길이
     *************************************************************/
    int commonLength =
        LCS(A, B);

    /*************************************************************
     * Shortest Common Supersequence Length
     *
     * |A| + |B| - LCS
     *************************************************************/
    int answer =
        A.size()
        + B.size()
        - commonLength;

    cout << answer << "\n";

    fin.close();

    return 0;
}