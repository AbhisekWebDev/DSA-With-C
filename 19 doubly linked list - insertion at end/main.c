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
    display();

    insertAtEnd();
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


void insertAtEnd(){

    newnode = (struct node *)malloc(sizeof(struct node));

    printf("\nEnter data at the end : \n");
    scanf("%d", &newnode -> data);

    newnode -> prev = newnode -> next = 0;

    tail -> next = newnode;
    newnode -> prev = tail;
    tail = newnode;
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

