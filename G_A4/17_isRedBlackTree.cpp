#include <iostream>   // 기본 입출력용 (이 문제 자체엔 꼭 필요하진 않지만 보통 함께 포함)
using namespace std;

// 노드의 색을 표현하기 위한 enum
// RED 또는 BLACK 두 값만 사용한다.
enum Color {
    RED,
    BLACK
};

// Red-Black Tree의 노드 구조체
struct Node {
    int key;          // 노드가 저장하는 정수 값
    Color color;      // 노드의 색 (RED 또는 BLACK)
    Node* left;       // 왼쪽 자식 포인터
    Node* right;      // 오른쪽 자식 포인터
};

// ------------------------------------------------------------
// checkRB:
// 현재 node를 루트로 하는 서브트리가 Red-Black Tree 조건을 만족하는지 검사하고,
// 동시에 그 서브트리의 black height를 bh에 저장한다.
//
// 반환값:
//   true  -> 이 서브트리는 Red-Black Tree 조건을 만족함
//   false -> 조건 위반
//
// 매개변수:
//   node : 현재 검사 중인 노드
//   bh   : 현재 서브트리의 black height를 돌려주기 위한 참조 변수
// ------------------------------------------------------------
bool checkRB(Node* node, int& bh) {
    // [기저 사례 1]
    // NULL 노드는 Red-Black Tree에서 "검정 리프"로 간주한다.
    // 따라서 NULL 자체는 항상 유효하다.
    if (node == NULL) {
        bh = 1;       // NULL을 black node 1개로 취급
        return true;  // 빈 트리는 조건을 깨지 않음
    }

    // 왼쪽/오른쪽 서브트리의 black height를 저장할 변수
    int leftBH = 0;
    int rightBH = 0;

    // --------------------------------------------------------
    // 1. 먼저 왼쪽 서브트리가 유효한 Red-Black Tree인지 검사
    //    유효하지 않으면 바로 false 반환
    // --------------------------------------------------------
    if (!checkRB(node->left, leftBH))
        return false;

    // --------------------------------------------------------
    // 2. 오른쪽 서브트리도 같은 방식으로 검사
    //    유효하지 않으면 바로 false 반환
    // --------------------------------------------------------
    if (!checkRB(node->right, rightBH))
        return false;

    // --------------------------------------------------------
    // 3. Red-Black Tree의 핵심 조건:
    //    빨간 노드의 자식은 반드시 검정이어야 한다.
    //
    //    즉, 현재 노드가 RED라면
    //    왼쪽 자식이나 오른쪽 자식이 RED이면 안 된다.
    // --------------------------------------------------------
    if (node->color == RED) {
        // 왼쪽 자식이 존재하고, 그 자식도 RED이면 위반
        if (node->left != NULL && node->left->color == RED)
            return false;

        // 오른쪽 자식이 존재하고, 그 자식도 RED이면 위반
        if (node->right != NULL && node->right->color == RED)
            return false;
    }

    // --------------------------------------------------------
    // 4. 또 다른 핵심 조건:
    //    현재 노드에서 모든 리프(NULL)까지 가는 경로의
    //    black node 수는 같아야 한다.
    //
    //    즉, 왼쪽 서브트리와 오른쪽 서브트리의 black height가 같아야 한다.
    // --------------------------------------------------------
    if (leftBH != rightBH)
        return false;

    // --------------------------------------------------------
    // 5. 현재 서브트리의 black height 계산
    //
    //    왼쪽과 오른쪽의 black height는 이미 같다고 확인했으므로
    //    둘 중 하나를 사용하면 된다.
    //
    //    현재 노드가 BLACK이면 black height에 1을 더하고,
    //    현재 노드가 RED이면 더하지 않는다.
    // --------------------------------------------------------
    if (node->color == BLACK)
        bh = leftBH + 1;
    else
        bh = leftBH;

    // 여기까지 왔으면 현재 서브트리는 Red-Black Tree 조건을 만족
    return true;
}

// ------------------------------------------------------------
// isRedBlackTree:
// 전체 트리가 Red-Black Tree인지 판정하는 함수
//
// Red-Black Tree의 최상위 조건 중 하나는
// "루트는 반드시 검정" 이므로 이것도 따로 검사한다.
// ------------------------------------------------------------
bool isRedBlackTree(Node* root) {
    // 빈 트리는 Red-Black Tree로 간주 가능
    if (root == NULL)
        return true;

    // 루트는 반드시 BLACK이어야 한다.
    if (root->color != BLACK)
        return false;

    // 전체 트리의 black height를 받아올 변수
    int blackHeight = 0;

    // 재귀 검사 함수 호출
    return checkRB(root, blackHeight);
}