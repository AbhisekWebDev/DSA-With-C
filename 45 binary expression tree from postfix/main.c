#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define a structure for tree nodes
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new tree node
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to construct an expression tree from a postfix expression
Node* constructTree(char* postfix) {
    Node* stack[100];
    int top = -1;
    Node *t, *t1, *t2;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (!isOperator(postfix[i])) {
            t = newNode(postfix[i]);
            stack[++top] = t;
        } else {
            t = newNode(postfix[i]);

            t1 = stack[top--];
            t2 = stack[top--];

            t->right = t1;
            t->left = t2;

            stack[++top] = t;
        }
    }

    t = stack[top--];
    return t;
}

// Function to perform inorder traversal of the tree
void inorder(Node* t) {
    if (t) {
        inorder(t->left);
        printf("%c ", t->data);
        inorder(t->right);
    }
}

int main() {
    char postfix[] = "ab+cde+**";  // Example postfix expression

    Node* r = constructTree(postfix);

    printf("Inorder traversal of the expression tree: ");
    inorder(r);

    return 0;
}
