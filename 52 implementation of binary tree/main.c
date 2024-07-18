#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};

// Function prototypes
struct node* create();

void inorderDisplay(struct node* root);

void preorderDisplay(struct node* root);

void postorderDisplay(struct node* root);

int main()
{
    struct node *root;

    root = 0;
    root = create();

    printf("The nodes in the binary tree are (inorder traversal) : ");
    inorderDisplay(root);

    printf("\n");

    printf("The nodes in the binary tree are (preorder traversal) : ");
    preorderDisplay(root);

    printf("\n");

    printf("The nodes in the binary tree are (postorder traversal) : ");
    postorderDisplay(root);

    return 0;
}

struct node *create(){
    int x;

    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    printf("Enter data or Enter '-1' for no node : ");
    scanf("%d", &x);

    printf("\n");

    if(x == -1)
        return 0;

    newnode -> data = x;

    printf("Enter left child of %d : \n", x);
    newnode -> left = create(); // use of recursion

    printf("Enter right child of %d : \n", x);
    newnode -> right = create(); // use of recursion

    return newnode;
}

// To display all the nodes in a binary tree,
// We can use an in-order traversal function.
// This will visit each node in the tree and print its data.
void inorderDisplay(struct node* root){
    if (root == NULL)
        return;

    inorderDisplay(root->left);
    printf("%d ", root->data);
    inorderDisplay(root->right);
}

// To display all the nodes in a binary tree,
// We can use an pre-order traversal function.
// This will visit each node in the tree and print its data.
void preorderDisplay(struct node* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorderDisplay(root->left);
    preorderDisplay(root->right);
}

// To display all the nodes in a binary tree,
// We can use an post-order traversal function.
// This will visit each node in the tree and print its data.
void postorderDisplay(struct node* root) {
    if (root == NULL)
        return;

    postorderDisplay(root->left);
    postorderDisplay(root->right);
    printf("%d ", root->data);
}
