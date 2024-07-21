#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to perform right rotation
struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Function to perform left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Function to splay the tree with the given key
struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (root->data > key) {
        if (root->left == NULL) return root;

        if (root->left->data > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->data < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    } else {
        if (root->right == NULL) return root;

        if (root->right->data > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        } else if (root->right->data < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Function to insert a new node into the Splay Tree
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) return createNode(key);

    root = splay(root, key);

    if (root->data == key) return root;

    struct Node* newNode = createNode(key);

    if (root->data > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }
    return newNode;
}

// Bottom-up deletion
struct Node* deleteBottomUp(struct Node* root, int key) {
    if (root == NULL) return NULL;

    root = splay(root, key);

    if (key != root->data) return root;

    if (root->left == NULL) {
        struct Node* temp = root;
        root = root->right;
        free(temp);
    } else {
        struct Node* temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
        free(temp);
    }

    return root;
}

// Recursive in-order traversal of the Splay Tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Recursive pre-order traversal of the Splay Tree
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Recursive post-order traversal of the Splay Tree
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Main function to demonstrate the Splay Tree with bottom-up deletion
int main() {
    struct Node* root = NULL;

    // Insert nodes into the Splay Tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("In-order traversal of the Splay Tree: ");
    inorderTraversal(root);
    printf("\n");

    // Delete nodes using bottom-up approach
    root = deleteBottomUp(root, 25);
    root = deleteBottomUp(root, 30);

    printf("In-order traversal after bottom-up deletions: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
