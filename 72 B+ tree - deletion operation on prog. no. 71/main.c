#include <stdio.h>
#include <stdlib.h>

// Define the minimum degree for the B+ tree (order 5)
#define MIN_DEGREE 5

// B+ tree node structure
struct BPTreeNode {
    char *keys; // Array of keys
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
    node->keys = (char*)malloc((2 * t - 1) * sizeof(char));
    node->C = (struct BPTreeNode**)malloc(2 * t * sizeof(struct BPTreeNode*));
    node->n = 0;
    node->next = NULL;
    return node;
}

// Function to traverse the B+ tree in inorder recursively
void inorderTraversalRecursive(struct BPTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                inorderTraversalRecursive(root->C[i]);
            printf("%c ", root->keys[i]);
        }
        if (!root->leaf)
            inorderTraversalRecursive(root->C[i]);
    }
}

// Function to insert a new key in the B+ tree
void insert(struct BPTreeNode** root, char k, int t) {
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
void insertNonFull(struct BPTreeNode* x, char k, int t) {
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

// Function to delete a key from the B+ tree
void deleteKey(struct BPTreeNode* root, char k);

// Function to delete a key from a non-leaf node
void deleteNonLeaf(struct BPTreeNode* x, char k);

// Function to delete a key from a leaf node
void deleteFromLeaf(struct BPTreeNode* x, char k);

// Function to find the predecessor of a key
char getPred(struct BPTreeNode* x, int idx);

// Function to find the successor of a key
char getSucc(struct BPTreeNode* x, int idx);

// Function to fill a node after deletion
void fill(struct BPTreeNode* x, int idx);

// Function to borrow a key from the previous sibling
void borrowFromPrev(struct BPTreeNode* x, int idx);

// Function to borrow a key from the next sibling
void borrowFromNext(struct BPTreeNode* x, int idx);

// Function to merge nodes
void merge(struct BPTreeNode* x, int idx);

// Implementations of the B+ tree deletion functions

void deleteKey(struct BPTreeNode* root, char k) {
    // Base case
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    // Call recursive delete function
    deleteNonLeaf(root, k);
}

void deleteNonLeaf(struct BPTreeNode* x, char k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k)
        idx++;

    // If the key is present in this node
    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf)
            deleteFromLeaf(x, k);
        else
            deleteFromInternal(x, idx);
    } else {
        if (x->leaf) {
            printf("The key %c is not present in the tree\n", k);
            return;
        }
        int flag = ((idx == x->n) ? 1 : 0);
        if (x->C[idx]->n < MIN_DEGREE)
            fill(x, idx);
        if (flag && idx > x->n)
            deleteNonLeaf(x->C[idx - 1], k);
        else
            deleteNonLeaf(x->C[idx], k);
    }
}

void deleteFromLeaf(struct BPTreeNode* x, char k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k)
        idx++;

    if (idx < x->n && x->keys[idx] == k) {
        for (int i = idx; i < x->n - 1; i++)
            x->keys[i] = x->keys[i + 1];
        x->n--;
    }
}

void deleteFromInternal(struct BPTreeNode* x, int idx) {
    char k = x->keys[idx];

    if (x->C[idx]->n >= MIN_DEGREE) {
        char pred = getPred(x, idx);
        deleteNonLeaf(x->C[idx], pred);
        x->keys[idx] = pred;
    } else if (x->C[idx + 1]->n >= MIN_DEGREE) {
        char succ = getSucc(x, idx);
        deleteNonLeaf(x->C[idx + 1], succ);
        x->keys[idx] = succ;
    } else {
        merge(x, idx);
        deleteNonLeaf(x->C[idx], k);
    }
}

char getPred(struct BPTreeNode* x, int idx) {
    struct BPTreeNode* cur = x->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

char getSucc(struct BPTreeNode* x, int idx) {
    struct BPTreeNode* cur = x->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

void fill(struct BPTreeNode* x, int idx) {
    if (idx != 0 && x->C[idx - 1]->n >= MIN_DEGREE)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->C[idx + 1]->n >= MIN_DEGREE)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx - 1);
    }
}

void borrowFromPrev(struct BPTreeNode* x, int idx) {
    struct BPTreeNode* child = x->C[idx];
    struct BPTreeNode* sibling = x->C[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = x->keys[idx - 1];
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    x->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}

void borrowFromNext(struct BPTreeNode* x, int idx) {
    struct BPTreeNode* child = x->C[idx];
    struct BPTreeNode* sibling = x->C[idx + 1];

    child->keys[child->n] = x->keys[idx];

    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n++;
    sibling->n--;
}

void merge(struct BPTreeNode* x, int idx) {
    struct BPTreeNode* child = x->C[idx];
    struct BPTreeNode* sibling = x->C[idx + 1];

    child->keys[MIN_DEGREE - 1] = x->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + MIN_DEGREE] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->C[i + MIN_DEGREE] = sibling->C[i];
    }

    for (int i = idx + 1; i < x->n; i++)
        x->C[i] = x->C[i + 1];

    for (int i = idx; i < x->n - 1; i++)
        x->keys[i] = x->keys[i + 1];

    child->n += sibling->n + 1;
    x->n--;

    free(sibling->keys);
    free(sibling->C);
    free(sibling);
}

// Main function to demonstrate B+ Tree
int main() {
    struct BPTreeNode* root = NULL;
    int t = MIN_DEGREE;

    // Insert alphabets into the B+ tree
    char keys[] = {'F', 'B', 'G', 'A', 'D', 'I', 'C', 'E', 'H'};
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&root, keys[i], t);
    }

    printf("In-order traversal (Recursive): ");
    inorderTraversalRecursive(root);
    printf("\n");

    // Delete a key from the B+ tree
    char keyToDelete = 'C';
    printf("Deleting key %c...\n", keyToDelete);
    deleteKey(root, keyToDelete);

    printf("In-order traversal after deletion: ");
    inorderTraversalRecursive(root);
    printf("\n");

    return 0;
}
