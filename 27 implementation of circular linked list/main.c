#include <stdio.h>
#include <stdlib.h>

struct node{

    int data;

    struct node *next;

} *head = 0, *newNode, *temp ;

int choice = 1, count = 0;

int main()
{

    printf("Implementation of circular linked list \n");

    create();

    display();

    return 0;
}

void create(){

    while(choice){

        newNode = (struct node*)malloc(sizeof(struct node));

        printf("Enter data : ");
        scanf("%d", &newNode -> data);

        newNode -> next = 0;

        if(head == 0){

            head = temp = newNode;
        } else {

            temp -> next = newNode;
            temp = newNode;
            temp -> next = head;
        }

        printf("0 to abort & 1 to continue (0, 1) \n");
        scanf("%d", &choice);
    }
}

void display(){

    temp = head;

    printf("Entered data: ");

    while(temp -> next != head){

        printf("%d", temp -> data);

        temp = temp -> next;

        count++;
    }

    printf("\nTotal number of nodes: %d\n", count);
}

