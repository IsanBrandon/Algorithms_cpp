#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Maximum Subarray Sum
 *
 * 목적:
 * - 배열에서 연속된 하나 이상의 원소를 선택했을 때
 *   만들 수 있는 최대합을 구한다.
 *
 * DP 정의:
 * cur = 현재 위치 i에서 반드시 끝나는 연속 부분배열의 최대합
 * best = 지금까지 발견한 전체 최대 연속 부분합
 *
 * 핵심 아이디어:
 *
 * i번째 원소 a[i]를 볼 때 선택지는 두 가지이다.
 *
 * 1. 이전 구간에 a[i]를 이어 붙인다.
 *    cur + a[i]
 *
 * 2. 이전 구간을 버리고 a[i]에서 새로 시작한다.
 *    a[i]
 *
 * 따라서:
 * cur = max(a[i], cur + a[i])
 *
 * 그리고 매번 best를 갱신한다.
 ***********************************************************************/
int maxSubarraySum(vector<int> &a) {
    /*
     * 문제에서 하나 이상의 원소를 반드시 선택해야 하므로
     * 첫 번째 원소로 초기화한다.
     */
    int cur = a[0];
    int best = a[0];

    for (int i = 1; i < (int)a.size(); i++) {
        /*
         * a[i]를 이전 연속 부분배열에 붙일지,
         * 아니면 a[i]부터 새로 시작할지 결정
         */
        cur = max(a[i], cur + a[i]);

        /*
         * 현재 위치에서 끝나는 최대합 cur가
         * 전체 최대합 best보다 크면 갱신
         */
        best = max(best, cur);
    }

    return best;
}

int main() {
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n;

    /*
     * n = 배열 원소 개수
     */
    fin >> n;

    vector<int> a(n);

    /*
     * 배열 입력
     */
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    /*
     * 최대 연속 부분합 출력
     */
    cout << maxSubarraySum(a) << "\n";

    fin.close();

    return 0;
}