#include <iostream>
#include <fstream>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Point 구조체
 *
 * 하나의 2차원 점을 표현한다.
 *
 * x: x좌표
 * y: y좌표
 *
 * 좌표 곱셈에서 overflow가 날 수 있으므로 long long 사용
 ***********************************************************************/
struct Point {
    long long x;
    long long y;
};

/***********************************************************************
 * ccw 함수
 *
 * 목적:
 * - 세 점 a, b, c의 방향을 판정한다.
 *
 * 계산:
 * - 벡터 AB와 벡터 AC의 외적을 계산한다.
 *
 * AB = (b.x - a.x, b.y - a.y)
 * AC = (c.x - a.x, c.y - a.y)
 *
 * 외적:
 * AB x AC
 * =
 * (b.x - a.x) * (c.y - a.y)
 * -
 * (b.y - a.y) * (c.x - a.x)
 *
 * 결과:
 * > 0 : 반시계 방향, CCW
 * < 0 : 시계 방향, CW
 * = 0 : 일직선, COLLINEAR
 ***********************************************************************/
long long ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

int main() {
    /*******************************************************************
     * input1.txt 파일 열기 확인
     *******************************************************************/
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    Point a, b, c;

    /*
     * 세 점 입력
     */
    fin >> a.x >> a.y;
    fin >> b.x >> b.y;
    fin >> c.x >> c.y;

    /*
     * 세 점의 방향 판정
     */
    long long result = ccw(a, b, c);

    if (result > 0) {
        cout << "CCW\n";
    }
    else if (result < 0) {
        cout << "CW\n";
    }
    else {
        cout << "COLLINEAR\n";
    }

    fin.close();

    return 0;
}