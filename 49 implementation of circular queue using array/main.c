#include <stdio.h>
#include <stdlib.h>

#define N 5

int queue[N], front = -1, rear = -1;

int main()
{
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);

    display();

    dequeue();

    display();

    peek();

    dequeue();

    display();

    enqueue(6);

    display();

    enqueue(7);

    display();

    enqueue(8);

    display();



    return 0;
}

void enqueue(int x){
    if(front == -1 && rear == -1){
        front = rear = 0;
        queue[rear] = x;
    }else if((rear + 1) % N == front)
        printf("Overflow condition \n");
    else{
        rear = (rear + 1) % N;
        queue[rear] = x;
    }
}

void dequeue(){
    if(front == -1 && rear == -1)
        printf("Underflow condition \n");
    else if(front == rear)
        front = rear = -1;
    else{
        printf("The dequeued element is : %d \n", queue[front]);
        front = (front + 1) % N;
    }
}

void display(){
    if(front == -1 && rear == -1)
        printf("Underflow condition");
    else{
        printf("The elements in the queue are : ");

        int i = front;

        while(i != rear){
            printf("%d ", queue[i]);
            i = (i + 1) % N;
        }
        printf("%d\n", queue[rear]); // print the last element
    }
}

void peek(){
    if(front == -1 && rear == -1)
        printf("Underflow condition");

    printf("The front most element in the queue is : %d \n", queue[front]);
}
