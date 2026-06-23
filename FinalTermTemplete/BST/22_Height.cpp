#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// input1.txt 파일에서 입력을 받기 위한 파일 입력 스트림
ifstream fin("input1.txt");

/***********************************************************************
 * Node 구조체
 *
 * BST의 각 노드를 표현한다.
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
 * key가 현재 노드보다 작으면 왼쪽,
 * 크거나 같으면 오른쪽에 삽입한다.
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
 * BST 높이 계산 함수
 *
 * 높이 정의:
 * - 루트에서 가장 멀리 있는 리프까지의 edge 개수
 *
 * 중요한 기준:
 * - 빈 트리의 높이 = -1
 * - 노드 1개짜리 트리의 높이 = 0
 *
 * 이유:
 * 노드 1개짜리 트리에서
 *
 * height(root)
 * = 1 + max(height(nullptr), height(nullptr))
 * = 1 + max(-1, -1)
 * = 0
 ***********************************************************************/
int heightBST(Node *root) {
    if (root == nullptr) {
        return -1;
    }

    int leftHeight = heightBST(root->left);
    int rightHeight = heightBST(root->right);

    return 1 + max(leftHeight, rightHeight);
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
     * 입력된 정수들을 순서대로 BST에 삽입
     *******************************************************************/
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;

        root = insertBST(root, x);
    }

    /*******************************************************************
     * BST 높이 출력
     *******************************************************************/
    cout << heightBST(root) << "\n";

    fin.close();

    return 0;
}