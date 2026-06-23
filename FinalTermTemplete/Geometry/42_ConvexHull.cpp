#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Point 구조체
 *
 * 평면 위의 한 점을 표현한다.
 *
 * x, y 좌표는 곱셈 과정에서 overflow가 날 수 있으므로 long long 사용
 ***********************************************************************/
struct Point {
    long long x;
    long long y;
};

/***********************************************************************
 * 점 정렬 기준
 *
 * x좌표가 작은 점이 먼저 온다.
 * x좌표가 같으면 y좌표가 작은 점이 먼저 온다.
 ***********************************************************************/
bool pointLess(Point a, Point b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }

    return a.y < b.y;
}

/***********************************************************************
 * CCW 함수
 *
 * 세 점 a, b, c에 대해
 * a -> b -> c가 어떤 방향으로 꺾이는지 계산한다.
 *
 * 결과:
 * > 0 : 반시계 방향
 * < 0 : 시계 방향
 * = 0 : 일직선
 ***********************************************************************/
long long ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

/***********************************************************************
 * Convex Hull: Monotonic Chain Algorithm
 *
 * 목적:
 * - 주어진 점들의 convex hull을 구성하는 점들을 구한다.
 *
 * 알고리즘 흐름:
 *
 * 1. 점들을 x좌표, y좌표 기준으로 정렬한다.
 *
 * 2. 아래쪽 껍질(lower hull)을 만든다.
 *    왼쪽에서 오른쪽으로 점을 보면서,
 *    마지막 세 점이 반시계 방향이 아니면 가운데 점을 제거한다.
 *
 * 3. 위쪽 껍질(upper hull)을 만든다.
 *    오른쪽에서 왼쪽으로 점을 보면서 같은 방식으로 처리한다.
 *
 * 4. lower와 upper를 합친다.
 *
 * 시간복잡도:
 * - 정렬 O(n log n)
 * - hull 구성 O(n)
 * - 전체 O(n log n)
 *
 * 주의:
 * - ccw <= 0일 때 pop하면 일직선상 가운데 점은 hull에서 제외된다.
 * - 일직선 위의 점까지 모두 포함하고 싶다면 ccw < 0으로 바꾼다.
 ***********************************************************************/
vector<Point> convexHull(vector<Point> p) {
    int n = p.size();

    /*
     * 점이 2개 이하이면 그 자체가 hull
     */
    if (n <= 2) {
        return p;
    }

    /*
     * 1. 점 정렬
     */
    sort(p.begin(), p.end(), pointLess);

    vector<Point> lower;
    vector<Point> upper;

    /*
     * 2. Lower Hull 구성
     *
     * 왼쪽에서 오른쪽으로 진행
     */
    for (Point pt : p) {
        /*
         * lower의 마지막 두 점과 새 점 pt를 봤을 때
         * 반시계 방향이 아니면 마지막 점 제거
         *
         * ccw <= 0:
         * - 시계 방향
         * - 일직선
         *
         * 둘 다 convex hull의 꼭짓점으로 부적절하다고 보고 제거
         */
        while (lower.size() >= 2 &&
               ccw(lower[lower.size() - 2], lower.back(), pt) <= 0) {
            lower.pop_back();
        }

        lower.push_back(pt);
    }

    /*
     * 3. Upper Hull 구성
     *
     * 오른쪽에서 왼쪽으로 진행
     */
    for (int i = n - 1; i >= 0; i--) {
        Point pt = p[i];

        while (upper.size() >= 2 &&
               ccw(upper[upper.size() - 2], upper.back(), pt) <= 0) {
            upper.pop_back();
        }

        upper.push_back(pt);
    }

    /*
     * lower와 upper에는 양 끝점이 중복으로 들어 있다.
     *
     * 예:
     * lower: A ... B
     * upper: B ... A
     *
     * 따라서 각각 마지막 점을 제거한 뒤 합친다.
     */
    lower.pop_back();
    upper.pop_back();

    /*
     * upper의 점들을 lower 뒤에 붙인다.
     */
    lower.insert(lower.end(), upper.begin(), upper.end());

    return lower;
}

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
     * 점 개수 입력
     */
    fin >> n;

    vector<Point> points(n);

    /*
     * 점 좌표 입력
     */
    for (int i = 0; i < n; i++) {
        fin >> points[i].x >> points[i].y;
    }

    /*
     * Convex Hull 계산
     */
    vector<Point> hull = convexHull(points);

    /*
     * Convex Hull을 이루는 점 개수 출력
     */
    cout << hull.size() << "\n";

    fin.close();

    return 0;
}