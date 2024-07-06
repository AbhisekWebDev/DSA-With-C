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

    insertAtSpecificPosition();
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


void insertAtSpecificPosition(){

    int pos, i = 1;

    printf("\nEnter position : \n");
    scanf("%d", &pos);

    int length = len();

    if(pos < 1 || pos > length){

        printf("Invalid position\n");
    }
    else{

        newnode = (struct node *)malloc(sizeof(struct node));

        printf("\nEnter data at the specific position : \n");
        scanf("%d", &newnode -> data);

        temp = head;

        while(i < pos - 1){

            temp = temp -> next;
            i++;
        }

        newnode -> prev = temp;
        newnode -> next = temp -> next;
        temp -> next = newnode;
        newnode -> next -> prev = newnode;
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


// i used this function to use in the insertAtSpecificPosition function
// to compare the length of nodes are smaller than inserted position or not

int len() {

    temp = head;

    count = 0;

    while (temp != 0) {

        count++;
        temp = temp->next;
    }

    return count;
}

