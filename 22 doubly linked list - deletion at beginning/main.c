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

    deleteAtBEginning();
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


void deleteAtBEginning(){

    printf("Remaining data after deletion from beginning : \n");

    if(head == 0)
        printf("List is empty");
    else{

        temp = head;
        head = head -> next;
        head -> prev = 0;

        free(temp);
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

