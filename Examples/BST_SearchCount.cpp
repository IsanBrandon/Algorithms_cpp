#include <iostream>
#include <fstream>

using namespace std;

// input1.txt 파일 열기
ifstream fin("input1.txt");

/*****************************************************************
 * BST 노드
 *
 * key   : 저장 값
 * left  : 왼쪽 자식
 * right : 오른쪽 자식
 *****************************************************************/
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        left = nullptr;
        right = nullptr;
    }
};

/*****************************************************************
 * BST 삽입
 *
 * 규칙:
 *
 * key < root
 * → 왼쪽
 *
 * key > root
 * → 오른쪽
 *
 * 중복은 저장하지 않음
 *****************************************************************/
Node* insertBST(Node* root, int key) {

    // 빈 위치 도착
    if (root == nullptr) {
        return new Node(key);
    }

    // 왼쪽으로 이동
    if (key < root->key) {
        root->left =
            insertBST(root->left, key);
    }

    // 오른쪽으로 이동
    else if (key > root->key) {
        root->right =
            insertBST(root->right, key);
    }

    return root;
}

/*****************************************************************
 * BST 탐색
 *
 * 반환:
 *
 * true  → 존재
 * false → 없음
 *
 * 시간복잡도:
 * O(h)
 *****************************************************************/
bool searchBST(Node* root, int target) {

    // 못 찾음
    if (root == nullptr)
        return false;

    // 찾음
    if (root->key == target)
        return true;

    // 왼쪽 탐색
    if (target < root->key) {
        return searchBST(
            root->left,
            target
        );
    }

    // 오른쪽 탐색
    return searchBST(
        root->right,
        target
    );
}

int main() {

    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n;
    fin >> n;

    Node* root = nullptr;

    /*************************************************************
     * BST 생성
     *************************************************************/
    for (int i = 0; i < n; i++) {

        int x;
        fin >> x;

        root =
            insertBST(root, x);
    }

    int q;
    fin >> q;

    int successCount = 0;

    /*************************************************************
     * q개의 검색 수행
     *************************************************************/
    for (int i = 0; i < q; i++) {

        int target;
        fin >> target;

        if (searchBST(root, target)) {
            successCount++;
        }
    }

    cout << successCount << "\n";

    fin.close();

    return 0;
}