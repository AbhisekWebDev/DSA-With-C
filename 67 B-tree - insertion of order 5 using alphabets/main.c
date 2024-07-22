#include <stdio.h>
#include <stdlib.h>

// B-Tree node structure
struct BTreeNode {
    char *keys; // Array of keys
    int t; // Minimum degree (defines the range for number of keys)
    struct BTreeNode **C; // Array of child pointers
    int n; // Current number of keys
    int leaf; // Is true when node is leaf. Otherwise false
};

// Function to create a new B-Tree node
struct BTreeNode* createNode(int t, int leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (char*)malloc((2 * t - 1) * sizeof(char));
    node->C = (struct BTreeNode**)malloc(2 * t * sizeof(struct BTreeNode*));
    node->n = 0;
    return node;
}

// Function to traverse the tree
void traverse(struct BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->C[i]);
        printf(" %c", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->C[i]);
}

// Function to insert a new key in the B-Tree
void insert(struct BTreeNode** root, char k, int t) {
    if (*root == NULL) {
        *root = createNode(t, 1);
        (*root)->keys[0] = k;
        (*root)->n = 1;
    } else {
        if ((*root)->n == 2 * t - 1) {
            struct BTreeNode* s = createNode(t, 0);
            s->C[0] = *root;
            splitChild(s, 0, *root, t);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->C[i], k, t);
            *root = s;
        } else {
            insertNonFull(*root, k, t);
        }
    }
}

// Function to insert a new key in a non-full node
void insertNonFull(struct BTreeNode* x, char k, int t) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && x->keys[i] > k)
            i--;
        if (x->C[i + 1]->n == 2 * t - 1) {
            splitChild(x, i + 1, x->C[i + 1], t);
            if (x->keys[i + 1] < k)
                i++;
        }
        insertNonFull(x->C[i + 1], k, t);
    }
}

// Function to split the child y of node x
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y, int t) {
    struct BTreeNode* z = createNode(t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    y->n = t - 1;
    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];
    x->C[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[t - 1];
    x->n = x->n + 1;
}

// Recursive inorder traversal
void inorderTraversal(struct BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            inorderTraversal(root->C[i]);
        printf(" %c", root->keys[i]);
    }
    if (!root->leaf)
        inorderTraversal(root->C[i]);
}

// Recursive preorder traversal
void preorderTraversal(struct BTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            printf(" %c", root->keys[i]);
            if (!root->leaf)
                preorderTraversal(root->C[i]);
        }
        if (!root->leaf)
            preorderTraversal(root->C[root->n]);
    }
}

// Recursive postorder traversal
void postorderTraversal(struct BTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i <= root->n; i++) {
            if (!root->leaf)
                postorderTraversal(root->C[i]);
        }
        for (int i = 0; i < root->n; i++) {
            printf(" %c", root->keys[i]);
        }
    }
}

// Main function to demonstrate B-Tree
int main() {
    struct BTreeNode* root = NULL;
    int t = 5; // Minimum degree

    // Insert nodes into the B-Tree
    char keys[] = {'A', 'G', 'F', 'B', 'K', 'D', 'H', 'M', 'J', 'E', 'S', 'I', 'R', 'X', 'C', 'L', 'N', 'T', 'U', 'P'};
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&root, keys[i], t);
    }

    printf("In-order traversal of the B-Tree:");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal of the B-Tree:");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal of the B-Tree:");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
