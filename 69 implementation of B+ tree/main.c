#include <stdio.h>
#include <stdlib.h>

// Define the minimum degree for the B+ tree
#define MIN_DEGREE 3

// B+ tree node structure
struct BPTreeNode {
    int *keys; // Array of keys
    int t; // Minimum degree (defines the range for number of keys)
    struct BPTreeNode **C; // Array of child pointers
    int n; // Current number of keys
    int leaf; // Is true when node is leaf. Otherwise false
    struct BPTreeNode *next; // Pointer to the next leaf node
};

// Function to create a new B+ tree node
struct BPTreeNode* createNode(int t, int leaf) {
    struct BPTreeNode* node = (struct BPTreeNode*)malloc(sizeof(struct BPTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    node->C = (struct BPTreeNode**)malloc(2 * t * sizeof(struct BPTreeNode*));
    node->n = 0;
    node->next = NULL;
    return node;
}

// Function to traverse the B+ tree in inorder
void inorderTraversal(struct BPTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                inorderTraversal(root->C[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            inorderTraversal(root->C[i]);
    }
}

// Function to traverse the B+ tree in preorder
void preorderTraversal(struct BPTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]);
        }
        for (int i = 0; i <= root->n; i++) {
            if (!root->leaf)
                preorderTraversal(root->C[i]);
        }
    }
}

// Function to traverse the B+ tree in postorder
void postorderTraversal(struct BPTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i <= root->n; i++) {
            if (!root->leaf)
                postorderTraversal(root->C[i]);
        }
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]);
        }
    }
}

// Function to insert a new key in the B+ tree
void insert(struct BPTreeNode** root, int k, int t) {
    if (*root == NULL) {
        *root = createNode(t, 1);
        (*root)->keys[0] = k;
        (*root)->n = 1;
    } else {
        if ((*root)->n == 2 * t - 1) {
            struct BPTreeNode* s = createNode(t, 0);
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
void insertNonFull(struct BPTreeNode* x, int k, int t) {
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
void splitChild(struct BPTreeNode* x, int i, struct BPTreeNode* y, int t) {
    struct BPTreeNode* z = createNode(t, y->leaf);
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

    if (y->leaf) {
        z->next = y->next;
        y->next = z;
    }
}

// Main function to demonstrate B+ tree
int main() {
    struct BPTreeNode* root = NULL;
    int t = MIN_DEGREE; // Minimum degree

    // Insert nodes into the B+ tree
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&root, keys[i], t);
    }

    printf("In-order traversal of the B+ tree: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order traversal of the B+ tree: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order traversal of the B+ tree: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}