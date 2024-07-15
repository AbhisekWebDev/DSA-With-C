#include <stdio.h>
#include <stdlib.h>

#define N 5

int queue[N];

int front = -1, rear = -1;

int main()
{
    enqueue(1);
    enqueue(2);
    enqueue(3);

    display();

    peek();

    dequeue();

    peek();

    display();

    return 0;
}

void enqueue(int x){
    if(rear == N - 1)
        printf("Overflow condition");
    else if(front == -1 && rear == -1){
        front = rear = 0;
        queue[rear] = x;
    }else{
        rear++;
        queue[rear] = x;
    }
}

void dequeue(){
    if(front == -1 && rear == -1)
        printf("Underflow condition");
    else if(front == rear)
        front = rear = -1;
    else{
        printf("The dequeued element is : %d \n", queue[front]);
        front++;
    }
}

void display(){
    if(front == -1 && rear == -1)
        printf("Underflow condition");
    else{
        printf("The elements in the queue are : ");
        for(int i = front ; i < rear + 1 ; i++)
            printf("%d", queue[i]);
        printf("\n");
    }
}

void peek(){
     if(front == -1 && rear == -1)
        printf("Underflow condition");
    else
        printf("The front most element is : %d \n", queue[front]);
}
