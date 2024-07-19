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

// Function to find the minimum value node in the BST
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) return root;
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display the BST in an in-order manner (recursive)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);  // Visit left subtree
        printf("%d ", root->data);     // Visit root node
        inorderTraversal(root->right); // Visit right subtree
    }
}

// Function to display the BST in a pre-order manner (recursive)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);     // Visit root node
        preorderTraversal(root->left);  // Visit left subtree
        preorderTraversal(root->right); // Visit right subtree
    }
}

// Function to display the BST in a post-order manner (recursive)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);  // Visit left subtree
        postorderTraversal(root->right); // Visit right subtree
        printf("%d ", root->data);     // Visit root node
    }
}

// Function to display the BST in an in-order manner (iterative)
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

// Function to display the BST in a pre-order manner (iterative)
void preorderTraversalIterative(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);

        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }
}

// Function to display the BST in a post-order manner (iterative)
void postorderTraversalIterative(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 != -1) {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left) stack1[++top1] = current->left;
        if (current->right) stack1[++top1] = current->right;
    }

    while (top2 != -1) {
        struct Node* current = stack2[top2--];
        printf("%d ", current->data);
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

    // Display the BST using recursive traversals
    printf("Recursive In-order traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Recursive Pre-order traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Recursive Post-order traversal: ");
    postorderTraversal(root);
    printf("\n");

    // Display the BST using iterative traversals
    printf("Iterative In-order traversal: ");
    inorderTraversalIterative(root);
    printf("\n");

    printf("Iterative Pre-order traversal: ");
    preorderTraversalIterative(root);
    printf("\n");

    printf("Iterative Post-order traversal: ");
    postorderTraversalIterative(root);
    printf("\n");

    // Delete a node and display the BST again
    root = deleteNode(root, 50);

    printf("In-order traversal after deleting 50: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal after deleting 50: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal after deleting 50: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}


// Explanation

// Node Structure:
// We define a structure Node that represents each node in the BST.
// It contains an integer data and pointers to the left and right child nodes.

// createNode Function:
// This function takes an integer data as input and creates a new node with this data.
// The left and right pointers are initialized to NULL.

// insertNode Function:
// This function inserts a new node with the given data into the BST.
// If the tree is empty (root is NULL), it creates a new node. Otherwise,
// it recursively finds the correct position for the new node in the left or right subtree.

// inorderTraversal Function:
// This function displays the BST in an in-order manner (left subtree, root node, right subtree).
// It uses recursion to traverse the tree.

// Pre-order Traversal:
// Visit the root node first, then recursively traverse the left subtree, and finally the right subtree.
// preorderTraversal function prints the node data first, then calls itself for the left and right subtrees.

// Post-order Traversal:
// Recursively traverse the left subtree first, then the right subtree, and finally visit the root node.
// postorderTraversal function calls itself for the left and right subtrees first, then prints the node data.

// Deletion of a Node:
// The deleteNode function removes a node from the BST. It handles three cases:
// The node to be deleted has no children.
// The node to be deleted has one child.
// The node to be deleted has two children (find the in-order successor to replace the deleted node).

// Iterative Traversal Functions:
// In-order Traversal: Uses a stack to simulate recursion. It pushes nodes onto the stack until it reaches the leftmost node, then processes nodes in LNR (Left-Node-Right) order.
// Pre-order Traversal: Uses a stack to process nodes in NLR (Node-Left-Right) order.
// Post-order Traversal: Uses two stacks to process nodes in LRN (Left-Right-Node) order.

// Main Function:
// We create an empty BST (root is NULL) and insert several nodes into it.
// Finally, we display the BST using in-order traversal.
// Deletion by removing the node with data 50 and showing the resulting tree.
