#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

struct Node {
    int data;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED; // New node is always red initially
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Function to fix violations after insertion
void fixInsertion(struct Node** root, struct Node* z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Function to insert a new node into the Red-Black Tree
void insert(struct Node** root, int data) {
    struct Node* z = createNode(data);
    struct Node* y = NULL;
    struct Node* x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsertion(root, z);
}

// Utility function to find the minimum node in the tree
struct Node* minimum(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Utility function to fix the tree after deletion
void fixDeletion(struct Node** root, struct Node* x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            struct Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Function to delete a node from the Red-Black Tree
void deleteNode(struct Node** root, struct Node* z) {
    struct Node* y = z;
    struct Node* x;
    Color yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (x != NULL) x->parent = z->parent;
        if (z->parent == NULL)
            *root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        free(z);
    } else if (z->right == NULL) {
        x = z->left;
        if (x != NULL) x->parent = z->parent;
        if (z->parent == NULL)
            *root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        free(z);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            if (x != NULL) x->parent = y->parent;
            y->parent->left = x;
            y->right = z->right;
            y->right->parent = y;
        }
        if (z->parent == NULL)
            *root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->parent = z->parent;
        y->color = z->color;
        y->left = z->left;
        y->left->parent = y;
        free(z);
    }
    if (yOriginalColor == BLACK && x != NULL)
        fixDeletion(root, x);
}

// In-order traversal of the Red-Black Tree (recursive)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Pre-order traversal of the Red-Black Tree (recursive)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Post-order traversal of the Red-Black Tree (recursive)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// In-order traversal of the Red-Black Tree (iterative)
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

// Pre-order traversal of the Red-Black Tree (iterative)
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

// Post-order traversal of the Red-Black Tree (iterative)
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

// Main function to demonstrate the Red-Black Tree
int main() {
    struct Node* root = NULL; // Create an empty Red-Black Tree

    // Insert nodes into the Red-Black Tree
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 25);

    printf("In-order traversal (recursive) of the Red-Black Tree: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal (recursive) of the Red-Black Tree: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal (recursive) of the Red-Black Tree: ");
    postorderTraversal(root);
    printf("\n");

    printf("In-order traversal (iterative) of the Red-Black Tree: ");
    inorderTraversalIterative(root);
    printf("\n");

    printf("Pre-order traversal (iterative) of the Red-Black Tree: ");
    preorderTraversalIterative(root);
    printf("\n");

    printf("Post-order traversal (iterative) of the Red-Black Tree: ");
    postorderTraversalIterative(root);
    printf("\n");

    // Delete nodes from the Red-Black Tree
    struct Node* nodeToDelete = root->right->right; // Node with value 50
    deleteNode(&root, nodeToDelete);
    nodeToDelete = root->right; // Node with value 30
    deleteNode(&root, nodeToDelete);

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
