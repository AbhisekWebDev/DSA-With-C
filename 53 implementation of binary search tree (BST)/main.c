#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data); // If tree is empty, create a new node
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data); // Insert in the left subtree
    } else {
        root->right = insertNode(root->right, data); // Insert in the right subtree
    }
    return root;
}

// Function to display the BST in an in-order manner
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);  // Visit left subtree
        printf("%d ", root->data);     // Visit root node
        inorderTraversal(root->right); // Visit right subtree
    }
}

// Function to display the BST in a pre-order manner
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);     // Visit root node
        preorderTraversal(root->left);  // Visit left subtree
        preorderTraversal(root->right); // Visit right subtree
    }
}

// Function to display the BST in a post-order manner
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);  // Visit left subtree
        postorderTraversal(root->right); // Visit right subtree
        printf("%d ", root->data);     // Visit root node
    }
}

// Main function to demonstrate the BST
int main() {
    struct Node* root = NULL; // Create an empty BST

    // Insert nodes into the BST
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);

    // Display the BST
    printf("In-order traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal of the BST: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal of the BST: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
