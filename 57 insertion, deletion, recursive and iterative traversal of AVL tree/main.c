#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of the tree
int height(struct Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;  // New node is initially added at leaf
    return newNode;
}

// A utility function to right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a data in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insertNode(struct Node* node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else  // Equal data are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + ((height(node->left) > height(node->right)) ? height(node->left) : height(node->right));

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Helper function to find the minimum value node in a subtree
struct Node* findMin(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Recursive function to delete a node from the subtree rooted
// with node and returns the new root of the subtree.
struct Node* deleteNode(struct Node* root, int data) {
    // Perform the normal BST deletion
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct Node* temp = findMin(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + ((height(root->left) > height(root->right)) ? height(root->left) : height(root->right));

    // Get the balance factor of this node
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to display the AVL tree in an in-order manner (recursive)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);  // Visit left subtree
        printf("%d ", root->data);     // Visit root node
        inorderTraversal(root->right); // Visit right subtree
    }
}

// Function to display the AVL tree in a pre-order manner (recursive)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);     // Visit root node
        preorderTraversal(root->left);  // Visit left subtree
        preorderTraversal(root->right); // Visit right subtree
    }
}

// Function to display the AVL tree in a post-order manner (recursive)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);  // Visit left subtree
        postorderTraversal(root->right); // Visit right subtree
        printf("%d ", root->data);     // Visit root node
    }
}

// Function to display the AVL tree in an in-order manner (iterative)
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

// Function to display the AVL tree in a pre-order manner (iterative)
void preorderTraversalIterative(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);

        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
}

// Function to display the AVL tree in a post-order manner (iterative)
void postorderTraversalIterative(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 != -1) {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL) {
            stack1[++top1] = current->left;
        }
        if (current->right != NULL) {
            stack1[++top1] = current->right;
        }
    }

    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
}

// Main function to demonstrate the AVL tree
int main() {
    struct Node* root = NULL; // Create an empty AVL tree

    // Insert nodes into the AVL tree
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    printf("In-order traversal (recursive) of the AVL tree: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal (recursive) of the AVL tree: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal (recursive) of the AVL tree: ");
    postorderTraversal(root);
    printf("\n");

    printf("In-order traversal (iterative) of the AVL tree: ");
    inorderTraversalIterative(root);
    printf("\n");

    printf("Pre-order traversal (iterative) of the AVL tree: ");
    preorderTraversalIterative(root);
    printf("\n");

    printf("Post-order traversal (iterative) of the AVL tree: ");
    postorderTraversalIterative(root);
    printf("\n");

    // Delete nodes from the AVL tree
    root = deleteNode(root, 40);
    root = deleteNode(root, 10);
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






// Explanation

// Node Structure:
// We define a structure Node that represents each node in the AVL tree.
// It contains an integer data, pointers to the left and right child nodes,
// and an integer height to store the height of the node.

// Height Function:
// This function returns the height of a given node. If the node is NULL, it returns 0.

// Create Node Function:
// This function creates a new node with the given data,
// initializes its left and right pointers to NULL, and sets its height to 1.

// Right Rotate Function:
// This function performs a right rotation on the subtree rooted with y and updates the heights of the affected nodes.

// Left Rotate Function:
// This function performs a left rotation on the subtree rooted with x and updates the heights of the affected nodes.

// Get Balance Function:
// This function calculates and returns the balance factor of a given node.

// Insert Node Function:
// This function inserts a new node with the given data into the AVL tree,
// performs necessary rotations to keep the tree balanced, and returns the new root of the subtree.

// In-order Traversal Function:
// This function displays the AVL tree in an in-order manner (left subtree, root node, right subtree).
// It uses recursion to traverse the tree.

// Pre-order Traversal Function:
// This function displays the AVL tree in a pre-order manner (root node, left subtree, right subtree).
// It uses recursion to traverse the tree.

// Post-order Traversal Function:
// This function displays the AVL tree in a post-order manner (left subtree, right subtree, root node).
// It uses recursion to traverse the tree.

// Delete Node Function:
// This function deletes a node with a given value from the AVL tree while maintaining the AVL property.
// It handles nodes with no children, one child, and two children.
// After deleting the node, it balances the tree by checking and handling imbalances.

// Iterative Traversals:

// In-order Traversal (Iterative): Uses a stack to simulate the recursive process for in-order traversal.

// Pre-order Traversal (Iterative): Uses a stack to simulate the recursive process for pre-order traversal.

// Post-order Traversal (Iterative): Uses two stacks to simulate the recursive process for post-order traversal.

// Main Function:
// We create an empty AVL tree (root is NULL) and insert several nodes into it.
// Finally, we display the AVL tree using in-order traversal.
// Shows how the AVL tree looks after deletions.
