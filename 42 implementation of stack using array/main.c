#include <stdio.h>
#include <stdlib.h>

#define N 5 // macro

int stack[N], top = -1;

// Function declarations
void push();
void pop();
void peek();
void display();

int main()
{
    printf("Implementation of stack using Array\n");

    int choice;

    do{
        printf("Enter choice : \n Press 1 for push() : \n press 2 for pop() : \n press 3 for peek() : \n press 4 for display() : \n Your choice : ");
        scanf("%d", &choice);

        switch(choice){
            case 1: push();
                    break;
            case 2: pop();
                    break;
            case 3: peek();
                    break;
            case 4: display();
                    break;
            default: printf("Invalid choice");
        }
    }while(choice != 0);

    return 0;
}

void push(){
    int x;

    printf("Enter data : ");
    scanf("%d", &x);

    if(top == N - 1)
        printf("Over flow condition");
    else{
        top++;
        stack[top] = x;
    }
}

void pop(){
    int item;
    if(top == -1)
        printf("Underflow condition");
    else{
        item = stack[top];
        top--;
        printf("Popped item : %d \n", item);
    }
}

void peek(){
    if(top == -1)
        printf("Stack is empty");
    else
        printf("Top item : %d \n", stack[top]);
}

void display(){
    printf("Stack elements : \n");
    for(int i = top ; i >= 0; i--)
        printf("%d", stack[i]);
    printf("\n");
}
