#include <stdio.h>
#include <stdlib.h>

struct node{

    int data;
    struct node *next;
};

struct node *head = 0, *newNode, *temp;

int main()
{
    create();

    printf("Before reversal \n");

    display();
    count();

    reverse();

    printf("After reversal \n");

    display();
    count();

    return 0;
}

void create(){

    int choice = 1;

    while(choice){

        newNode = (struct node*)malloc(sizeof(struct node));

        printf("Enter data \n");
        scanf("%d", &newNode -> data);

        newNode -> next = 0;

        if(head == 0){

            head = temp = newNode;
        } else {

            temp -> next = newNode;
            temp = newNode;
        }

        printf("0 to abort & 1 to continue (0, 1) \n");
        scanf("%d", &choice);
    }
}

void display(){

    temp = head;

    printf("Entered data: \n");

    while(temp != 0){

        printf("%d ", temp -> data);

        temp = temp -> next;
    }

    printf("\n");
}

void count(){

    int count = 0;

    temp = head;

    while(temp != 0){

        temp = temp->next;

        count++;
    }

    printf("\nTotal number of nodes: %d\n", count);
}

void reverse(){

    struct node *prevnode, *currentnode, *nextnode;

    prevnode = 0;
    currentnode = nextnode = head;

    while(nextnode != 0){

        nextnode = nextnode -> next;
        currentnode -> next = prevnode;
        prevnode = currentnode;
        currentnode = nextnode;
    }

    head = prevnode;
}
