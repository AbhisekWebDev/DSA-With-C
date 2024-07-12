#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
} *head, *tail, *temp, *newnode;

int main()
{
    create();
    display();

    insertAtBeginning();
    display();

    return 0;
}

void create() {
    int choice = 1;

    while(choice){

        newnode = (struct node *)malloc(sizeof(struct node));

        printf("Enter data : ");
        scanf("%d", &newnode -> data);

        if(head == 0){
            head = tail = newnode;
            head -> next = head;
            head -> prev = head;
        }else{
            tail -> next = newnode;
            newnode -> prev = tail;
            newnode -> next = head; // head hi rkhna kyunki head always points to the first node in the list
            head -> prev = newnode;
            tail = newnode;
        }

        printf("0 to abort & 1 to continue (0, 1): ");
        scanf("%d", &choice);
    }

    printf("Accessing the first data in the list through the tail pointer : %d \n", tail -> next -> data);
    printf("Accessing the last data in the list through the head pointer :%d \n", head -> prev -> data);
}

void insertAtBeginning() {
    newnode = (struct node *)malloc(sizeof(struct node));

    printf("Enter data at the beginning : ");
    scanf("%d", &newnode -> data);

    if(head == 0){
        head = tail = newnode;
        newnode -> prev = tail;
        newnode -> next = head;
    }else{
        newnode -> next = head;
        head -> prev = newnode;
        newnode -> prev = tail;
        tail -> next = newnode;
        head = newnode;
    }

    printf("Data after insertion at the beginning : ");
}

void display() {
    temp = head;

    int count = 0;

    if(head == 0) {
        printf("List is empty\n");
    }

    do {
        printf("%d ", temp->data);
        temp = temp->next;
        count++;
    } while(temp != head);

    printf("\nTotal number of nodes: %d\n", count);
}
