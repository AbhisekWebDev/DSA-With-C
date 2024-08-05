#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* find_min(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* delete(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

int extract_min(Node** root) {
    if (*root == NULL) {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    Node* min_node = find_min(*root);
    int min_value = min_node->data;
    *root = delete(*root, min_value);
    return min_value;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 15);
    root = insert(root, 30);
    root = insert(root, 40);

    printf("Priority Queue (in-order): ");
    inorder(root);
    printf("\n");

    printf("Extracted min: %d\n", extract_min(&root));
    printf("Priority Queue after extraction (in-order): ");
    inorder(root);
    printf("\n");

    return 0;
}
