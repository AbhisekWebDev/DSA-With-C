#include <stdio.h>
#include <stdlib.h>

#define N 5

int stack1[N], stack2[N], top1 = -1; top2 = -1, count = 0;

int main()
{
    enqueue(1);
    enqueue(2);
    enqueue(3);

    display();

    printf("After another enqueue : \n");
    enqueue(4);

    display();

    return 0;
}

void push1(int data){
    if(top1 == N - 1)
        printf("Overflow condition");
    else{
        top1++;
        stack1[top1] = data;
    }
}

int pop1(){
    return stack1[top1--];
}

void push2(int data){
    if(top2 == N - 1)
        printf("Overflow condition");
    else{
        top2++;
        stack2[top2] = data;
    }
}

int pop2(){
    return stack2[top2--];
}

void enqueue(int x){
    push1(x);
    count++;
}

void dequeue(){
    int a, b;
    if(top1 == -1 && top2 == -1)
        printf("Underflow condition");
    else{
        for(int i = 0 ; i < count ; i++){
            a = pop1();
            push2(a);
        }
        b = pop2();
        printf("The dequeued element is : %d", b);
        count--;
        for(int i = 0 ; i < count ; i++){
            a = pop2();
            push1(a);
        }
    }
}

void display(){
    printf("The elements in the queue using stack are : ");
    for(int i = 0 ; i <= top1 ; i++)
        printf("%d", stack1[i]);
    printf("\n");
}
