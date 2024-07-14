#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
} *top = 0, *temp; // yaha pr top ka matlab head h

void push(int x){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    newnode -> data = x;
    newnode -> next = top;
    top = newnode;
}

void display(){
    temp = top;
    if(top == 0)
        printf("List is empty");
    else{
        printf("The elements in the stack are : ");
        while(temp != 0){
            printf("%d ", temp -> data);
            temp = temp -> next;
        }
    }
}

void pop(){
    temp = top;
    if(top == 0)
        printf("List is empty");
    else{
        printf("The popped element is : %d ", top -> data);
        top = top -> next;
        free(temp);
    }
}

void peek(){
    if(top == 0)
        printf("List is empty");
    else
        printf("\nTop element is : %d \n", top -> data);
}

int main()
{
    push(2);
    push(3);
    push(10);

    display();

    peek();

    pop();

    peek();

    display();

    return 0;
}

