#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Frequency Count
 *
 * 목적:
 * - n개의 문자열을 입력받아
 *   각 문자열이 몇 번 등장했는지 센다.
 *
 * 자료구조:
 * - map<string, int> freq
 *
 * 왜 map을 사용하는가?
 * - key: 문자열
 * - value: 등장 횟수
 * - map은 key를 자동으로 오름차순 정렬해서 저장한다.
 *
 * 따라서 출력할 때 문자열이 사전순으로 출력된다.
 *
 * 만약 정렬 순서가 필요 없다면 unordered_map을 사용해도 된다.
 ***********************************************************************/

int main() {
    /*******************************************************************
     * input1.txt 파일 열기 확인
     *******************************************************************/
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n;

    /*
     * n = 입력받을 문자열 개수
     */
    fin >> n;

    /*
     * freq[word] = word가 등장한 횟수
     *
     * map은 문자열 key를 자동으로 사전순 정렬한다.
     */
    map<string, int> freq;

    /*
     * n개의 문자열 입력
     *
     * fin >> word는 공백, 줄바꿈을 모두 기준으로 문자열을 읽는다.
     */
    for (int i = 0; i < n; i++) {
        string word;
        fin >> word;

        /*
         * word가 처음 등장했다면 freq[word]는 자동으로 0으로 만들어진다.
         * 그 후 1 증가한다.
         */
        freq[word]++;
    }

    /*
     * 결과 출력
     *
     * map은 key 기준으로 정렬되어 있으므로
     * 사전순으로 출력된다.
     */
    for (auto item : freq) {
        string word = item.first;
        int count = item.second;

        cout << word << " " << count << "\n";
    }

    fin.close();

    return 0;
}