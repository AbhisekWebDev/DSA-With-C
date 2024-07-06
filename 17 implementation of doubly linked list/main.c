#include <stdio.h>
#include <stdlib.h>


struct node {

    int data;

    struct node *prev, *next;
};

struct node *head, *newnode, *temp;

int choice = 1, count = 0;


int main()
{
    create();
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

            head = temp = newnode;
        }
        else{

            temp -> next = newnode;
            newnode -> prev = temp;
            temp = newnode;
        }

        printf("0 to abort & 1 to continue (0, 1) \n");
        scanf("%d", &choice);
    }
}


void display(){

    temp = head;

    printf("Entered data: ");

    while(temp != 0){

        printf("%d", temp -> data);

        temp = temp -> next;

        count++;
    }

    printf("\nTotal number of nodes: %d\n", count);
}
