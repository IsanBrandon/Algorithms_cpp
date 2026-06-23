#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * distinctInWindow
 *
 * 목적:
 * - 배열 a에서 길이가 k인 모든 연속 구간에 대해
 *   서로 다른 원소의 개수를 구한다.
 *
 * 핵심 아이디어:
 * - Sliding Window + Hash
 *
 * 윈도우란?
 * - 현재 보고 있는 길이 k짜리 구간
 *
 * 예:
 * a = [1, 2, 1, 3, 4, 2, 3], k = 4
 *
 * 첫 번째 window: [1, 2, 1, 3]
 * 두 번째 window: [2, 1, 3, 4]
 * 세 번째 window: [1, 3, 4, 2]
 *
 * 한 칸씩 오른쪽으로 이동한다.
 *
 * 자료구조:
 * - unordered_map<int, int> cnt
 *
 * cnt[x] = 현재 window 안에서 x가 등장한 횟수
 *
 * 서로 다른 원소의 개수는 cnt.size()와 같다.
 ***********************************************************************/
vector<int> distinctInWindow(vector<int> &a, int k) {
    unordered_map<int, int> cnt;
    vector<int> ans;

    for (int i = 0; i < (int)a.size(); i++) {
        /***************************************************************
         * 1. 새로 들어온 원소 추가
         *
         * 현재 위치 i의 원소가 window에 들어온다.
         ***************************************************************/
        cnt[a[i]]++;

        /***************************************************************
         * 2. window 크기가 k를 초과하면 가장 왼쪽 원소 제거
         *
         * 현재 i번째 원소까지 넣은 상태에서
         * window에 포함되어야 하는 원소는
         *
         * a[i-k+1] ~ a[i]
         *
         * 이다.
         *
         * 따라서 i >= k이면 a[i-k]는 window 밖으로 나가야 한다.
         ***************************************************************/
        if (i >= k) {
            cnt[a[i - k]]--;

            /*
             * 어떤 값의 등장 횟수가 0이 되면
             * 현재 window에 더 이상 존재하지 않는다는 뜻.
             *
             * 따라서 map에서 제거해야 cnt.size()가 정확한
             * 서로 다른 원소 개수가 된다.
             */
            if (cnt[a[i - k]] == 0) {
                cnt.erase(a[i - k]);
            }
        }

        /***************************************************************
         * 3. window 크기가 정확히 k가 된 순간부터 답 저장
         *
         * i >= k-1이면
         * 길이 k짜리 window가 완성된 상태이다.
         ***************************************************************/
        if (i >= k - 1) {
            ans.push_back(cnt.size());
        }
    }

    return ans;
}

int main() {
    /*******************************************************************
     * input1.txt 파일 열기 확인
     *******************************************************************/
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n, k;

    /*
     * n = 배열 길이
     * k = window 길이
     */
    fin >> n >> k;

    vector<int> a(n);

    /*
     * 배열 입력
     */
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    /*
     * 길이 k 구간별 서로 다른 원소 개수 계산
     */
    vector<int> ans = distinctInWindow(a, k);

    /*
     * 결과 출력
     */
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << "\n";

    fin.close();

    return 0;
}