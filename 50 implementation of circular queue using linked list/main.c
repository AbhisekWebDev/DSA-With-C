#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
}*front = 0, *rear = 0, *temp;

int main()
{
    enqueue(1);
    enqueue(2);
    enqueue(3);

    display();

    dequeue();

    display();

    peek();

    display();

    return 0;
}

void enqueue(int x){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    newnode -> data = x;
    newnode -> next = 0;

    if(rear == 0){
        front = rear = newnode;
        rear -> next = front; // Making it circular
    }else{
        rear -> next = newnode;
        rear = newnode;
        rear -> next = front; // Maintaining the circular link
    }
}

void dequeue(){
    temp = front;

    if(front == 0)
        printf("Underflow condition");
    else if(front == rear){
        front = rear = 0;

        free(temp);
    }else{
        printf("The dequeued element is : %d \n", front -> data);
        front = front -> next;
        rear -> next = front;

        free(temp);
    }
}

void peek(){
    if(front == 0 && rear == 0)
        printf("Underflow condition");

    printf("The front most element in the queue is : %d \n", front -> data);
}

void display(){
    temp = front;

     if(front == 0 && rear == 0)
        printf("Underflow condition");

    printf("The elements in the queue are : ");
    do{
        printf("%d", temp -> data);
        temp = temp -> next;
    }while(temp != front);

    printf("\n");
}
