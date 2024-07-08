#include <stdio.h>
#include <stdlib.h>


struct node {

    int data;

    struct node *prev, *next;
};

struct node *head, *newnode, *temp, *tail;

int choice = 1, count;


int main()
{
    create();

    printf("Before reversing the doubly linked list");
    display();

    reverseTheDoublyLinkedList();

    printf("After reversing the doubly linked list");
    display();

    return 0;
}


void create(){

    head = 0;

    while(choice){

        newnode = (struct node *)malloc(sizeof(struct node));

        printf("Enter data : ");
        scanf("%d", &newnode -> data);

        newnode -> prev = newnode -> next = 0;

        if(head == 0){

            head = tail = newnode;
        }
        else{

            tail -> next = newnode;
            newnode -> prev = tail;
            tail = newnode;
        }

        printf("0 to abort & 1 to continue (0, 1) \n");
        scanf("%d", &choice);
    }
}


void reverseTheDoublyLinkedList() {

    struct node *currentnode, *nextnode;

    if(head == 0)
        printf("List is empty");
    else{

        currentnode = head;

        while(currentnode != 0){

            nextnode = currentnode -> next;

            // nodes swapping logic
            currentnode -> next = currentnode -> prev;
            currentnode -> prev = nextnode;
            currentnode = nextnode;
        }

        printf("Before swapping : head = %d & tail = %d \n", head -> data, tail -> data);

        // head tail swapping logic
        currentnode = head;
        head = tail;
        tail = currentnode;

        printf("After swapping : head = %d & tail = %d \n", head -> data, tail -> data);
    }
}


void display(){

    count = 0;

    temp = head;

    printf("Entered data: ");

    while(temp != 0){

        printf("%d", temp -> data);

        temp = temp -> next;

        count++;
    }

    printf("\nTotal number of nodes: %d\n", count);
}
