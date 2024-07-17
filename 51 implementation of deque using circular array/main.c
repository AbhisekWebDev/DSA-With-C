#include <stdio.h>
#include <stdlib.h>

#define N 5

int deque[N], front = -1, rear = -1;

int main()
{
    enqueueFront(1);
    enqueueRear(2);

    enqueueFront(3);
    enqueueRear(4);

    display();

    getFront();
    getRear();

    enqueueFront(5);
    enqueueRear(6);

    dequeueFront();
    dequeueRear();

    display();

    return 0;
}

void enqueueFront(int x){
    if((front == 0 && rear == N - 1) || (front == rear + 1))
        printf("Overflow condition \n");
    else if(front == -1 && rear == -1){
        front = rear = 0;
        deque[front] = x;
    }
    else if(front == 0){
        front = N - 1;
        deque[front] = x;
    }
    else{
        front--;
        deque[front] = x;
    }
}

void enqueueRear(int x){
    if((front == 0 && rear == N - 1) || (front == rear + 1))
        printf("Overflow condition \n");
    else if(front == -1 && rear == -1){
        front = rear = 0;
        deque[rear] = x;
    }
    else if(rear == N - 1){
        rear = 0;
        deque[rear] = x;
    }
    else{
        rear++;
        deque[rear] = x;
    }
}

void display(){
    int i = front;

    if(front == -1 && rear == -1)
        printf("Underflow condition \n");

    printf("The elements in the DEQUE are : ");

    while(i != rear){
        printf("%d", deque[i]);
        i = (i + 1) % N;
    }
    printf("%d", deque[rear]);

    printf("\n");
}

void getFront(){
     if(front == -1 && rear == -1)
        printf("Underflow condition \n");

    printf("The front most element is : %d \n", deque[front]);
}

void getRear(){
     if(front == -1 && rear == -1)
        printf("Underflow condition \n");

    printf("The rear most element is : %d \n", deque[rear]);
}

void dequeueFront(){
    if(front == -1 && rear == -1)
        printf("Underflow condition \n");
    else if(front == rear){ // if only one element is present
        printf("The dequeued element is : %d \n", deque[front]);
        front = rear = -1;
    }
    else if(front == N - 1){
        printf("The dequeued element is : %d \n", deque[front]);
        front = 0;
    }
    else{
        printf("The dequeued element is : %d \n", deque[front]);
        front++;
    }
}

void dequeueRear(){
    if(front == -1 && rear == -1)
        printf("Underflow condition");
    else if(front == rear){ // if only one element is present
        printf("The dequeued element is : %d \n", deque[rear]);
        front = rear = -1;
    }
    else if(rear == 0){
        printf("The dequeued element is : %d \n", deque[rear]);
        rear =  N - 1;
    }
    else{
        printf("The dequeued element is : %d \n", deque[rear]);
        rear--;
    }
}
