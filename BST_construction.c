#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}


TreeNode* bstConstruct(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;


    TreeNode* node = createNode(postOrder[*postIndex]);
    (*postIndex)--;


    if (inStart == inEnd)
        return node;


    int inIndex = findIndex(inOrder, inStart, inEnd, node->data);


    node->right = bstConstruct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);

    node->left = bstConstruct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return node;
}


void bfsTraversal(TreeNode* root) {
    if (root == NULL)
        return;


    TreeNode* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        TreeNode* current = queue[++front];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[++rear] = current->left;
        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    int postIndex = n - 1;

    TreeNode* root = bstConstruct(inOrder, postOrder, 0, n - 1, &postIndex);


    printf("BST Construction:\n");
    printf("In-order traversal: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", inOrder[i]);
    }
    printf("\nPost-order traversal: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", postOrder[i]);
    }
    printf("\n");


    printf("BFS Traversal:\n");
    bfsTraversal(root);

    return 0;
}
