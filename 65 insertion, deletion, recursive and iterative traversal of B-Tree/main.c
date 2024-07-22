#include <stdio.h>
#include <stdlib.h>

// B-Tree node structure
struct BTreeNode {
    int *keys; // Array of keys
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
    node->keys = (int*)malloc((2 * t - 1) * sizeof(int));
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
        printf(" %d", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->C[i]);
}

// Function to search a key in the B-Tree
struct BTreeNode* search(struct BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == k)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->C[i], k);
}

// Function to insert a new key in the B-Tree
void insert(struct BTreeNode** root, int k, int t) {
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
void insertNonFull(struct BTreeNode* x, int k, int t) {
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

// A utility function to remove a key from the subtree rooted with this node
void removeKey(struct BTreeNode* root, int k, int t);

// A function to get predecessor of keys[i]
int getPred(struct BTreeNode* root, int i) {
    struct BTreeNode* cur = root->C[i];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// A function to get successor of keys[i]
int getSucc(struct BTreeNode* root, int i) {
    struct BTreeNode* cur = root->C[i + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// A function to remove the key k from the node which is a leaf
void removeFromLeaf(struct BTreeNode* root, int i) {
    for (int j = i + 1; j < root->n; ++j)
        root->keys[j - 1] = root->keys[j];
    root->n--;
}

// A function to remove the key k from the node which is a non-leaf
void removeFromNonLeaf(struct BTreeNode* root, int i, int t) {
    int k = root->keys[i];
    if (root->C[i]->n >= t) {
        int pred = getPred(root, i);
        root->keys[i] = pred;
        removeKey(root->C[i], pred, t);
    } else if (root->C[i + 1]->n >= t) {
        int succ = getSucc(root, i);
        root->keys[i] = succ;
        removeKey(root->C[i + 1], succ, t);
    } else {
        merge(root, i, t);
        removeKey(root->C[i], k, t);
    }
}

// A function to merge C[i] and C[i+1] of a node
void merge(struct BTreeNode* root, int i, int t) {
    struct BTreeNode* child = root->C[i];
    struct BTreeNode* sibling = root->C[i + 1];
    child->keys[t - 1] = root->keys[i];
    for (int j = 0; j < sibling->n; ++j)
        child->keys[j + t] = sibling->keys[j];
    if (!child->leaf) {
        for (int j = 0; j <= sibling->n; ++j)
            child->C[j + t] = sibling->C[j];
    }
    for (int j = i + 1; j < root->n; ++j)
        root->keys[j - 1] = root->keys[j];
    for (int j = i + 2; j <= root->n; ++j)
        root->C[j - 1] = root->C[j];
    child->n += sibling->n + 1;
    root->n--;
    free(sibling);
}

// A function to fill C[i] child if it has less than t-1 keys
void fill(struct BTreeNode* root, int i, int t) {
    if (i != 0 && root->C[i - 1]->n >= t)
        borrowFromPrev(root, i);
    else if (i != root->n && root->C[i + 1]->n >= t)
        borrowFromNext(root, i);
    else {
        if (i != root->n)
            merge(root, i, t);
        else
            merge(root, i - 1, t);
    }
}

// A function to borrow a key from the root->C[i-1] and insert it into root->C[i]
void borrowFromPrev(struct BTreeNode* root, int i) {
    struct BTreeNode* child = root->C[i];
    struct BTreeNode* sibling = root->C[i - 1];
    for (int j = child->n - 1; j >= 0; --j)
        child->keys[j + 1] = child->keys[j];
    if (!child->leaf) {
        for (int j = child->n; j >= 0; --j)
            child->C[j + 1] = child->C[j];
    }
    child->keys[0] = root->keys[i - 1];
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];
    root->keys[i - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

// A function to borrow a key from the root->C[i+1] and place it in root->C[i]
void borrowFromNext(struct BTreeNode* root, int i) {
    struct BTreeNode* child = root->C[i];
    struct BTreeNode* sibling = root->C[i + 1];
    child->keys[child->n] = root->keys[i];
    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];
    root->keys[i] = sibling->keys[0];
    for (int j = 1; j < sibling->n; ++j)
        sibling->keys[j - 1] = sibling->keys[j];
    if (!sibling->leaf) {
        for (int j = 1; j <= sibling->n; ++j)
            sibling->C[j - 1] = sibling->C[j];
    }
    child->n += 1;
    sibling->n -= 1;
}

// Function to remove a key from the B-Tree
void removeKey(struct BTreeNode* root, int k, int t) {
    int idx = 0;
    while (idx < root->n && root->keys[idx] < k)
        ++idx;
    if (idx < root->n && root->keys[idx] == k) {
        if (root->leaf)
            removeFromLeaf(root, idx);
        else
            removeFromNonLeaf(root, idx, t);
    } else {
        if (root->leaf) {
            printf("The key %d does not exist in the tree\n", k);
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
    if (root->n == 0) {
        struct BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
        free(tmp);
    }
}

// Recursive inorder traversal
void inorderTraversal(struct BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            inorderTraversal(root->C[i]);
        printf(" %d", root->keys[i]);
    }
    if (!root->leaf)
        inorderTraversal(root->C[i]);
}

// Recursive preorder traversal
void preorderTraversal(struct BTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            printf(" %d", root->keys[i]);
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
            printf(" %d", root->keys[i]);
        }
    }
}

// Iterative inorder traversal
void iterativeInorderTraversal(struct BTreeNode* root) {
    if (root == NULL) return;

    struct BTreeNode** stack = (struct BTreeNode**)malloc(100 * sizeof(struct BTreeNode*));
    int* indexes = (int*)malloc(100 * sizeof(int));
    int top = 0;
    stack[top] = root;
    indexes[top] = 0;
    while (top >= 0) {
        struct BTreeNode* node = stack[top];
        int index = indexes[top];
        if (index == node->n) {
            if (!node->leaf) {
                stack[top] = node->C[index];
                indexes[top] = 0;
            } else {
                top--;
            }
        } else {
            if (!node->leaf) {
                stack[top + 1] = node->C[index];
                indexes[top + 1] = 0;
                indexes[top]++;
                top++;
            } else {
                printf(" %d", node->keys[index]);
                indexes[top]++;
            }
        }
    }
    free(stack);
    free(indexes);
}

// Iterative preorder traversal
void iterativePreorderTraversal(struct BTreeNode* root) {
    if (root == NULL) return;

    struct BTreeNode** stack = (struct BTreeNode**)malloc(100 * sizeof(struct BTreeNode*));
    int top = 0;
    stack[top] = root;
    while (top >= 0) {
        struct BTreeNode* node = stack[top--];
        for (int i = 0; i < node->n; i++) {
            printf(" %d", node->keys[i]);
            if (!node->leaf) {
                stack[++top] = node->C[i];
            }
        }
        if (!node->leaf) {
            stack[++top] = node->C[node->n];
        }
    }
    free(stack);
}

// Iterative postorder traversal
void iterativePostorderTraversal(struct BTreeNode* root) {
    if (root == NULL) return;

    struct BTreeNode** stack = (struct BTreeNode**)malloc(100 * sizeof(struct BTreeNode*));
    struct BTreeNode** out = (struct BTreeNode**)malloc(100 * sizeof(struct BTreeNode*));
    int top = 0, outTop = 0;
    stack[top] = root;
    while (top >= 0) {
        struct BTreeNode* node = stack[top--];
        out[outTop++] = node;
        for (int i = 0; i <= node->n; i++) {
            if (!node->leaf) {
                stack[++top] = node->C[i];
            }
        }
    }
    while (outTop > 0) {
        struct BTreeNode* node = out[--outTop];
        for (int i = 0; i < node->n; i++) {
            printf(" %d", node->keys[i]);
        }
    }
    free(stack);
    free(out);
}

// Main function to demonstrate B-Tree
int main() {
    struct BTreeNode* root = NULL;
    int t = 3; // Minimum degree

    // Insert nodes into the B-Tree
    insert(&root, 10, t);
    insert(&root, 20, t);
    insert(&root, 5, t);
    insert(&root, 6, t);
    insert(&root, 12, t);
    insert(&root, 30, t);
    insert(&root, 7, t);
    insert(&root, 17, t);

    printf("Recursive In-order traversal of the B-Tree:");
    inorderTraversal(root);
    printf("\n");

    printf("Recursive Pre-order traversal of the B-Tree:");
    preorderTraversal(root);
    printf("\n");

    printf("Recursive Post-order traversal of the B-Tree:");
    postorderTraversal(root);
    printf("\n");

    printf("Iterative In-order traversal of the B-Tree:");
    iterativeInorderTraversal(root);
    printf("\n");

    printf("Iterative Pre-order traversal of the B-Tree:");
    iterativePreorderTraversal(root);
    printf("\n");

    printf("Iterative Post-order traversal of the B-Tree:");
    iterativePostorderTraversal(root);
    printf("\n");

    // Delete nodes from the B-Tree
    printf("Deleting 6\n");
    removeKey(root, 6, t);
    printf("In-order traversal of the B-Tree after deleting 6:");
    inorderTraversal(root);
    printf("\n");

    printf("Deleting 13\n");
    removeKey(root, 13, t);
    printf("In-order traversal of the B-Tree after deleting 13:");
    inorderTraversal(root);
    printf("\n");

    printf("Deleting 7\n");
    removeKey(root, 7, t);
    printf("In-order traversal of the B-Tree after deleting 7:");
    inorderTraversal(root);
    printf("\n");

    printf("Deleting 4\n");
    removeKey(root, 4, t);
    printf("In-order traversal of the B-Tree after deleting 4:");
    inorderTraversal(root);
    printf("\n");

    printf("Deleting 2\n");
    removeKey(root, 2, t);
    printf("In-order traversal of the B-Tree after deleting 2:");
    inorderTraversal(root);
    printf("\n");

    printf("Deleting 16\n");
    removeKey(root, 16, t);
    printf("In-order traversal of the B-Tree after deleting 16:");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
