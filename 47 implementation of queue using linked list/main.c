#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
} *front = 0, *rear = 0, *temp;

int main()
{
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);

    display();

    peek();

    dequeue();

    display();

    dequeue();

    display();

    return 0;
}

void enqueue(int x){
    // **** (struct node*) me typecasting ka zrurt isply prta h kyunki malloc - void pointer return krta h ****
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode -> data = x;
    newnode -> next = 0;
    if(front == 0 && rear == 0)
        front = rear = newnode;
    else{
        rear -> next = newnode;
        rear = newnode;
    }
}

void display(){
     if(front == 0 && rear == 0)
        printf("Underflow condition");
    else{
        printf("The elements in the queue using linked list are : ");

        temp = front;

        while(temp != 0){
            printf("%d", temp -> data);
            temp = temp -> next;
        }
        printf("\n");
    }
}

void dequeue(){
    if(front == 0 && rear == 0)
        printf("Underflow condition");

    temp = front;

    printf("The dequeued element is : %d \n", front -> data);

    front = front -> next;
    free(temp);
}

void peek(){
    if(front == 0 && rear == 0)
        printf("Underflow condition");

    printf("The front most element is : %d \n", front -> data);
}
