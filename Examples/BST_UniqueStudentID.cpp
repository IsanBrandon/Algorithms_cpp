#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

ifstream fin("input1.txt");

/*
 * BST 노드 구조체
 */
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

/*
 * BST 삽입 함수
 *
 * 중복값은 삽입하지 않는다.
 */
Node* insertBST(Node *root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insertBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }

    // key == root->key이면 중복이므로 아무것도 하지 않음
    return root;
}

/*
 * Inorder Traversal
 *
 * BST를 중위순회하면 오름차순으로 출력된다.
 */
void inorder(Node *root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->key << "\n";
    inorder(root->right);
}

int main() {
    if (!fin) {
        cout << "Cannot open input1.txt\n";
        return 0;
    }

    int n;
    fin >> n;

    Node *root = nullptr;

    // 서로 다른 ID 개수 확인용
    unordered_set<int> uniqueIDs;

    for (int i = 0; i < n; i++) {
        int id;
        fin >> id;

        // set에 넣으면 중복은 자동으로 무시됨
        uniqueIDs.insert(id);

        // BST에도 중복 없이 삽입
        root = insertBST(root, id);
    }

    // 서로 다른 학생 수 출력
    cout << uniqueIDs.size() << "\n\n";

    // 오름차순 출력
    inorder(root);

    fin.close();

    return 0;
}