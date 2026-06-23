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
 * left  : 왼쪽 자식 노드 주소
 * right : 오른쪽 자식 노드 주소
 ***********************************************************************/
struct Node {
    int key;
    Node *left;
    Node *right;

    /*
     * 생성자
     *
     * 새 노드를 만들 때 key 값을 저장하고,
     * 왼쪽/오른쪽 자식은 아직 없으므로 nullptr로 초기화한다.
     */
    Node(int key) {
        this->key = key;
        left = nullptr;
        right = nullptr;
    }
};

/***********************************************************************
 * BST 삽입 함수
 *
 * 목적:
 * - root를 루트로 하는 BST에 key를 삽입한다.
 *
 * BST 규칙:
 * - 현재 노드보다 작은 값은 왼쪽 서브트리로 간다.
 * - 현재 노드보다 크거나 같은 값은 오른쪽 서브트리로 간다.
 *
 * 반환값:
 * - 삽입 후의 루트 노드 주소
 *
 * 왜 반환값이 Node*인가?
 * - root가 nullptr인 빈 트리에 처음 삽입할 때,
 *   새 노드가 루트가 되어야 하기 때문이다.
 ***********************************************************************/
Node* insertBST(Node *root, int key) {
    /*
     * 현재 위치가 비어 있으면
     * 여기에 새 노드를 만들어 삽입한다.
     */
    if (root == nullptr) {
        return new Node(key);
    }

    /*
     * key가 현재 노드 값보다 작으면 왼쪽 서브트리에 삽입
     */
    if (key < root->key) {
        root->left = insertBST(root->left, key);
    }

    /*
     * key가 현재 노드 값보다 크거나 같으면 오른쪽 서브트리에 삽입
     */
    else {
        root->right = insertBST(root->right, key);
    }

    /*
     * 현재 루트 주소를 다시 반환
     */
    return root;
}

/***********************************************************************
 * 중위순회 Inorder Traversal
 *
 * 순서:
 * 1. 왼쪽 서브트리 방문
 * 2. 현재 노드 출력
 * 3. 오른쪽 서브트리 방문
 *
 * BST에서 inorder traversal을 하면
 * 값들이 오름차순으로 출력된다.
 ***********************************************************************/
void inorderBST(Node *root) {
    /*
     * 빈 노드이면 아무것도 하지 않고 종료
     */
    if (root == nullptr) {
        return;
    }

    inorderBST(root->left);

    cout << root->key << "\n";

    inorderBST(root->right);
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
     * 삽입할 정수 개수 입력
     */
    fin >> n;

    /*
     * 처음에는 빈 트리
     */
    Node *root = nullptr;

    /*
     * 정수들을 순서대로 BST에 삽입
     */
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;

        root = insertBST(root, x);
    }

    /*
     * 중위순회 출력
     */
    inorderBST(root);

    fin.close();

    return 0;
}