#include <iostream>
#include <fstream>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Node 구조체
 *
 * BST의 각 노드를 표현한다.
 *
 * key   : 노드에 저장된 값
 * left  : 왼쪽 자식
 * right : 오른쪽 자식
 ***********************************************************************/
struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int key) {
        this->key = key;
        left = nullptr;
        right = nullptr;
    }
};

/***********************************************************************
 * BST 삽입 함수
 *
 * BST 규칙:
 * - key < root->key 이면 왼쪽 서브트리
 * - key >= root->key 이면 오른쪽 서브트리
 ***********************************************************************/
Node* insertBST(Node *root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insertBST(root->left, key);
    } else {
        root->right = insertBST(root->right, key);
    }

    return root;
}

/***********************************************************************
 * BST 탐색 함수
 *
 * 목적:
 * - root를 루트로 하는 BST에서 target을 찾는다.
 *
 * 반환:
 * - target이 존재하면 true
 * - 존재하지 않으면 false
 *
 * 핵심:
 * BST에서는 현재 노드와 target을 비교해서
 * 한쪽 서브트리만 탐색하면 된다.
 *
 * 1. target == root->key
 *    찾음
 *
 * 2. target < root->key
 *    target은 왼쪽에 있을 수 있다.
 *
 * 3. target > root->key
 *    target은 오른쪽에 있을 수 있다.
 ***********************************************************************/
bool searchBST(Node *root, int target) {
    /*
     * 빈 노드까지 내려왔다는 것은
     * target이 트리에 없다는 뜻이다.
     */
    if (root == nullptr) {
        return false;
    }

    /*
     * 현재 노드에서 target 발견
     */
    if (target == root->key) {
        return true;
    }

    /*
     * target이 현재 노드 값보다 작으면
     * 왼쪽 서브트리 탐색
     */
    if (target < root->key) {
        return searchBST(root->left, target);
    }

    /*
     * target이 현재 노드 값보다 크면
     * 오른쪽 서브트리 탐색
     */
    return searchBST(root->right, target);
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
    fin >> n;

    Node *root = nullptr;

    /*******************************************************************
     * n개의 정수를 BST에 삽입
     *******************************************************************/
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;

        root = insertBST(root, x);
    }

    int target;
    fin >> target;

    /*******************************************************************
     * target 탐색 결과 출력
     *******************************************************************/
    if (searchBST(root, target)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    fin.close();

    return 0;
}