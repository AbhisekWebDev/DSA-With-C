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

// Function to traverse the B+ tree in inorder recursively
void inorderTraversalRecursive(struct BPTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                inorderTraversalRecursive(root->C[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            inorderTraversalRecursive(root->C[i]);
    }
}

// Function to traverse the B+ tree in preorder recursively
void preorderTraversalRecursive(struct BPTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]);
        }
        for (int i = 0; i <= root->n; i++) {
            if (!root->leaf)
                preorderTraversalRecursive(root->C[i]);
        }
    }
}

// Function to traverse the B+ tree in postorder recursively
void postorderTraversalRecursive(struct BPTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i <= root->n; i++) {
            if (!root->leaf)
                postorderTraversalRecursive(root->C[i]);
        }
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]);
        }
    }
}

// Function to traverse the B+ tree in inorder iteratively
void inorderTraversalIterative(struct BPTreeNode* root) {
    if (root == NULL) return;
    struct BPTreeNode* current = root;
    while (current->leaf == 0)
        current = current->C[0];
    while (current != NULL) {
        for (int i = 0; i < current->n; i++) {
            printf("%d ", current->keys[i]);
        }
        current = current->next;
    }
}

// Function to traverse the B+ tree in preorder iteratively
void preorderTraversalIterative(struct BPTreeNode* root) {
    if (root == NULL) return;
    struct BPTreeNode* stack[1000];
    int top = -1;
    stack[++top] = root;
    while (top >= 0) {
        struct BPTreeNode* node = stack[top--];
        for (int i = 0; i < node->n; i++) {
            printf("%d ", node->keys[i]);
        }
        if (!node->leaf) {
            for (int i = node->n; i >= 0; i--) {
                stack[++top] = node->C[i];
            }
        }
    }
}

// Function to traverse the B+ tree in postorder iteratively
void postorderTraversalIterative(struct BPTreeNode* root) {
    if (root == NULL) return;
    struct BPTreeNode* stack1[1000];
    struct BPTreeNode* stack2[1000];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 >= 0) {
        struct BPTreeNode* node = stack1[top1--];
        stack2[++top2] = node;
        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++) {
                stack1[++top1] = node->C[i];
            }
        }
    }
    while (top2 >= 0) {
        struct BPTreeNode* node = stack2[top2--];
        for (int i = 0; i < node->n; i++) {
            printf("%d ", node->keys[i]);
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

// Function to remove a key from the B+ tree
void removeKey(struct BPTreeNode* root, int k, int t) {
    if (root == NULL) return;

    int idx = findKey(root, k);

    if (idx < root->n && root->keys[idx] == k) {
        if (root->leaf)
            removeFromLeaf(root, idx);
        else
            removeFromNonLeaf(root, idx, t);
    } else {
        if (root->leaf) {
            printf("The key %d is not present in the tree\n", k);
            return;
        }

        int flag = (idx == root->n);

        if (root->C[idx]->n < t)
            fill(root, idx, t);

        if (flag && idx > root->n)
            removeKey(root->C[idx - 1], k, t);
        else
            removeKey(root->C[idx], k, t);
    }
}

// Function to find the key in the node
int findKey(struct BPTreeNode* root, int k) {
    int idx = 0;
    while (idx < root->n && root->keys[idx] < k)
        ++idx;
    return idx;
}

// Function to remove the key from a leaf node
void removeFromLeaf(struct BPTreeNode* root, int idx) {
    for (int i = idx + 1; i < root->n; ++i)
        root->keys[i - 1] = root->keys[i];
    root->n--;
}

// Function to remove the key from a non-leaf node
void removeFromNonLeaf(struct BPTreeNode* root, int idx, int t) {
    int k = root->keys[idx];

    if (root->C[idx]->n >= t) {
        int pred = getPred(root, idx);
        root->keys[idx] = pred;
        removeKey(root->C[idx], pred, t);
    } else if (root->C[idx + 1]->n >= t) {
        int succ = getSucc(root, idx);
        root->keys[idx] = succ;
        removeKey(root->C[idx + 1], succ, t);
    } else {
        merge(root, idx, t);
        removeKey(root->C[idx], k, t);
    }
}

// Function to get the predecessor of the key
int getPred(struct BPTreeNode* root, int idx) {
    struct BPTreeNode* cur = root->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// Function to get the successor of the key
int getSucc(struct BPTreeNode* root, int idx) {
    struct BPTreeNode* cur = root->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// Function to fill the child node
void fill(struct BPTreeNode* root, int idx, int t) {
    if (idx != 0 && root->C[idx - 1]->n >= t)
        borrowFromPrev(root, idx);
    else if (idx != root->n && root->C[idx + 1]->n >= t)
        borrowFromNext(root, idx);
    else {
        if (idx != root->n)
            merge(root, idx, t);
        else
            merge(root, idx - 1, t);
    }
}

// Function to borrow a key from the previous child
void borrowFromPrev(struct BPTreeNode* root, int idx) {
    struct BPTreeNode* child = root->C[idx];
    struct BPTreeNode* sibling = root->C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = root->keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    root->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

// Function to borrow a key from the next child
void borrowFromNext(struct BPTreeNode* root, int idx) {
    struct BPTreeNode* child = root->C[idx];
    struct BPTreeNode* sibling = root->C[idx + 1];

    child->keys[child->n] = root->keys[idx];

    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];

    root->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// Function to merge two child nodes
void merge(struct BPTreeNode* root, int idx, int t) {
    struct BPTreeNode* child = root->C[idx];
    struct BPTreeNode* sibling = root->C[idx + 1];

    child->keys[t - 1] = root->keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < root->n; ++i)
        root->keys[i - 1] = root->keys[i];

    for (int i = idx + 2; i <= root->n; ++i)
        root->C[i - 1] = root->C[i];

    child->n += sibling->n + 1;
    root->n--;

    free(sibling);
}

// Main function to demonstrate B+ Tree
int main() {
    struct BPTreeNode* root = NULL;
    int t = MIN_DEGREE;

    // Insert nodes into the B+ tree
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&root, keys[i], t);
    }

    printf("In-order traversal (Recursive): ");
    inorderTraversalRecursive(root);
    printf("\n");

    printf("Pre-order traversal (Recursive): ");
    preorderTraversalRecursive(root);
    printf("\n");

    printf("Post-order traversal (Recursive): ");
    postorderTraversalRecursive(root);
    printf("\n");

    printf("In-order traversal (Iterative): ");
    inorderTraversalIterative(root);
    printf("\n");

    printf("Pre-order traversal (Iterative): ");
    preorderTraversalIterative(root);
    printf("\n");

    printf("Post-order traversal (Iterative): ");
    postorderTraversalIterative(root);
    printf("\n");

    printf("Removing key 6\n");
    removeKey(root, 6, t);
    printf("In-order traversal after deletion: ");
    inorderTraversalRecursive(root);
    printf("\n");

    return 0;
}
