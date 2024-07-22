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

// Function prototypes
struct BTreeNode* createNode(int t, int leaf);
void traverse(struct BTreeNode* root);
void insert(struct BTreeNode** root, char k, int t);
void insertNonFull(struct BTreeNode* x, char k, int t);
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y, int t);
void removeKey(struct BTreeNode* x, char k, int t);
void removeFromLeaf(struct BTreeNode* x, int idx);
void removeFromNonLeaf(struct BTreeNode* x, int idx, int t);
char getPred(struct BTreeNode* x, int idx);
char getSucc(struct BTreeNode* x, int idx);
void fill(struct BTreeNode* x, int idx, int t);
void borrowFromPrev(struct BTreeNode* x, int idx);
void borrowFromNext(struct BTreeNode* x, int idx);
void merge(struct BTreeNode* x, int idx, int t);
void inorderTraversal(struct BTreeNode* root);
void preorderTraversal(struct BTreeNode* root);
void postorderTraversal(struct BTreeNode* root);

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

// Function to find the index of the first key that is greater or equal to k
int findKey(struct BTreeNode* x, char k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k)
        ++idx;
    return idx;
}

// Function to remove a key from a B-Tree
void removeKey(struct BTreeNode* x, char k, int t) {
    int idx = findKey(x, k);

    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf)
            removeFromLeaf(x, idx);
        else
            removeFromNonLeaf(x, idx, t);
    } else {
        if (x->leaf) {
            printf("The key %c is not present in the tree\n", k);
            return;
        }
        int flag = (idx == x->n) ? 1 : 0;

        if (x->C[idx]->n < t)
            fill(x, idx, t);

        if (flag && idx > x->n)
            removeKey(x->C[idx - 1], k, t);
        else
            removeKey(x->C[idx], k, t);
    }
    return;
}

// Function to remove a key from a leaf node
void removeFromLeaf(struct BTreeNode* x, int idx) {
    for (int i = idx + 1; i < x->n; ++i)
        x->keys[i - 1] = x->keys[i];
    x->n--;
    return;
}

// Function to remove a key from a non-leaf node
void removeFromNonLeaf(struct BTreeNode* x, int idx, int t) {
    char k = x->keys[idx];

    if (x->C[idx]->n >= t) {
        char pred = getPred(x, idx);
        x->keys[idx] = pred;
        removeKey(x->C[idx], pred, t);
    } else if (x->C[idx + 1]->n >= t) {
        char succ = getSucc(x, idx);
        x->keys[idx] = succ;
        removeKey(x->C[idx + 1], succ, t);
    } else {
        merge(x, idx, t);
        removeKey(x->C[idx], k, t);
    }
    return;
}

// Function to get the predecessor of keys[idx]
char getPred(struct BTreeNode* x, int idx) {
    struct BTreeNode* cur = x->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// Function to get the successor of keys[idx]
char getSucc(struct BTreeNode* x, int idx) {
    struct BTreeNode* cur = x->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// Function to fill a child node which has less than t keys
void fill(struct BTreeNode* x, int idx, int t) {
    if (idx != 0 && x->C[idx - 1]->n >= t)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->C[idx + 1]->n >= t)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx, t);
        else
            merge(x, idx - 1, t);
    }
    return;
}

// Function to borrow a key from the previous child node
void borrowFromPrev(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->C[idx];
    struct BTreeNode* sibling = x->C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = x->keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    x->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// Function to borrow a key from the next child node
void borrowFromNext(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->C[idx];
    struct BTreeNode* sibling = x->C[idx + 1];

    child->keys[child->n] = x->keys[idx];

    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

// Function to merge two child nodes of x
void merge(struct BTreeNode* x, int idx, int t) {
    struct BTreeNode* child = x->C[idx];
    struct BTreeNode* sibling = x->C[idx + 1];

    child->keys[t - 1] = x->keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < x->n; ++i)
        x->keys[i - 1] = x->keys[i];

    for (int i = idx + 2; i <= x->n; ++i)
        x->C[i - 1] = x->C[i];

    child->n += sibling->n + 1;
    x->n--;

    free(sibling);
    return;
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

    // Perform deletion operation
    char delKeys[] = {'R', 'M', 'K'};
    for (int i = 0; i < sizeof(delKeys) / sizeof(delKeys[0]); i++) {
        printf("\nDeleting key %c:\n", delKeys[i]);
        removeKey(root, delKeys[i], t);
        printf("In-order traversal after deletion:");
        inorderTraversal(root);
        printf("\n");
    }

    return 0;
}
