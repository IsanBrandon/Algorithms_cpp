struct Node {
    int key;
    Node *left;
    Node *right;
};

// 현재 서브트리의 지름을 반환하고,
// height에는 현재 서브트리의 높이(에지 수 기준)를 저장한다.
int getDiameter(Node *root, int &height) {
    // 빈 트리
    if (root == nullptr) {
        height = -1;   // 에지 수 기준에서 NULL의 높이는 -1
        return 0;      // 빈 트리의 지름은 0
    }

    // 왼쪽/오른쪽 서브트리의 높이
    int leftHeight, rightHeight;

    // 왼쪽/오른쪽 서브트리의 지름
    int leftDiameter = getDiameter(root->left, leftHeight);
    int rightDiameter = getDiameter(root->right, rightHeight);

    // 현재 노드의 높이 계산
    height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);

    // 현재 노드를 지나는 경로의 길이
    int throughRoot = leftHeight + rightHeight + 2;

    // 세 경우 중 최대가 현재 서브트리의 지름
    int ans = throughRoot;
    if (leftDiameter > ans) ans = leftDiameter;
    if (rightDiameter > ans) ans = rightDiameter;

    return ans;
}

