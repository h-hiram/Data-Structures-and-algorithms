#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node *left, *right;
};


struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}


struct Node* insert(struct Node* root, int key) {
    if (root == NULL) return newNode(key);
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}


struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


int height(struct Node* root) {
    if (root == NULL) return -1;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}


void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found!\n");
        return;
    }
    if (root->data == key) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
        return;
    }
    if (key < root->data)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;


    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");


    root = deleteNode(root, 25);
    printf("Inorder traversal after deleting node 25: ");
    inorder(root);
    printf("\n");


    printf("Height of the BST: %d\n", height(root));


    int key = 40;
    printLevelAndHeight(root, key, 0);

    return 0;
}
