#include <stdio.h>
#include <stdlib.h>

// Define the structure for a threaded tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int leftThread;  // 1 if left pointer is a thread, 0 if it points to a left child
    int rightThread; // 1 if right pointer is a thread, 0 if it points to a right child
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->leftThread = 1;
    newNode->rightThread = 1;
    return newNode;
}

// Function to insert a node into the threaded binary tree
struct Node* insertNode(struct Node* root, int data) {
    struct Node* parent = NULL;
    struct Node* current = root;

    while (current != NULL) {
        parent = current;
        if (data == current->data) {
            printf("Duplicate key!\n");
            return root;
        }
        if (data < current->data) {
            if (current->leftThread == 0)
                current = current->left;
            else
                break;
        } else {
            if (current->rightThread == 0)
                current = current->right;
            else
                break;
        }
    }

    struct Node* newNode = createNode(data);
    if (parent == NULL) {
        root = newNode;
    } else if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->leftThread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rightThread = 0;
        parent->right = newNode;
    }
    return root;
}

// Function to find the in-order successor of a node
struct Node* inOrderSuccessor(struct Node* node) {
    if (node->rightThread == 1)
        return node->right;
    node = node->right;
    while (node->leftThread == 0)
        node = node->left;
    return node;
}

// Function to traverse the threaded binary tree in-order
void inOrderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* current = root;
    while (current->leftThread == 0)
        current = current->left;

    while (current != NULL) {
        printf("%d ", current->data);
        current = inOrderSuccessor(current);
    }
}

// Function to delete a node from the threaded binary tree
struct Node* deleteNode(struct Node* root, int data) {
    struct Node* parent = NULL;
    struct Node* current = root;
    int found = 0;

    while (current != NULL) {
        if (data == current->data) {
            found = 1;
            break;
        }
        parent = current;
        if (data < current->data) {
            if (current->leftThread == 0)
                current = current->left;
            else
                break;
        } else {
            if (current->rightThread == 0)
                current = current->right;
            else
                break;
        }
    }

    if (!found) {
        printf("Node not found!\n");
        return root;
    }

    struct Node* target = current;
    if (current->leftThread == 0 && current->rightThread == 0) {
        parent = current;
        target = current->left;
        while (target->rightThread == 0) {
            parent = target;
            target = target->right;
        }
        current->data = target->data;
        data = target->data;
    }

    if (target->leftThread == 1 && target->rightThread == 1) {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == target) {
            parent->leftThread = 1;
            parent->left = target->left;
        } else {
            parent->rightThread = 1;
            parent->right = target->right;
        }
    } else if (target->leftThread == 0) {
        struct Node* child = target->left;
        if (parent == NULL)
            root = child;
        else if (parent->left == target)
            parent->left = child;
        else
            parent->right = child;
        struct Node* s = inOrderSuccessor(target);
        struct Node* p = NULL;
        if (target->rightThread == 1)
            s->left = p;
        else
            s->left = target->right;
    } else {
        struct Node* child = target->right;
        if (parent == NULL)
            root = child;
        else if (parent->left == target)
            parent->left = child;
        else
            parent->right = child;
        struct Node* s = target->left;
        while (s->rightThread == 0)
            s = s->right;
        s->right = target->right;
    }
    free(target);
    return root;
}

// Main function to demonstrate the threaded binary tree
int main() {
    struct Node* root = NULL; // Create an empty threaded binary tree

    // Insert nodes into the threaded binary tree
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);

    // Display the threaded binary tree using in-order traversal
    printf("In-order traversal of the threaded binary tree: ");
    inOrderTraversal(root);
    printf("\n");

    // Delete a node and display the threaded binary tree again
    root = deleteNode(root, 50);
    printf("In-order traversal after deleting 50: ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
