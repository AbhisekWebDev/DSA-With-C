#include <stdio.h>
#include <stdlib.h>

// Define the structure of a tree node
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

// Function to delete a node from the Splay Tree
struct Node* deleteNode(struct Node* root, int key) {
    struct Node* temp;
    if (root == NULL) return NULL;

    root = splay(root, key);

    if (key != root->data) return root;

    if (root->left == NULL) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);
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

// Iterative in-order traversal of the Splay Tree
void inorderTraversalIterative(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Iterative pre-order traversal of the Splay Tree
void preorderTraversalIterative(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node* node = stack[top--];
        printf("%d ", node->data);

        if (node->right != NULL)
            stack[++top] = node->right;
        if (node->left != NULL)
            stack[++top] = node->left;
    }
}

// Iterative post-order traversal of the Splay Tree
void postorderTraversalIterative(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 != -1) {
        struct Node* node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left != NULL)
            stack1[++top1] = node->left;
        if (node->right != NULL)
            stack1[++top1] = node->right;
    }

    while (top2 != -1) {
        struct Node* node = stack2[top2--];
        printf("%d ", node->data);
    }
}

// Main function to demonstrate the Splay Tree
int main() {
    struct Node* root = NULL;

    // Insert nodes into the Splay Tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("In-order traversal (recursive) of the Splay Tree: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal (recursive) of the Splay Tree: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal (recursive) of the Splay Tree: ");
    postorderTraversal(root);
    printf("\n");

    printf("In-order traversal (iterative) of the Splay Tree: ");
    inorderTraversalIterative(root);
    printf("\n");

    printf("Pre-order traversal (iterative) of the Splay Tree: ");
    preorderTraversalIterative(root);
    printf("\n");

    printf("Post-order traversal (iterative) of the Splay Tree: ");
    postorderTraversalIterative(root);
    printf("\n");

    // Delete nodes from the Splay Tree
    root = deleteNode(root, 25);
    root = deleteNode(root, 30);

    printf("In-order traversal (recursive) after deletions: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal (recursive) after deletions: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal (recursive) after deletions: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
