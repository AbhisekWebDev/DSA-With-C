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

    getLength();

    deleteAtSpecificPosition();
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

void deleteAtSpecificPosition() {
    int pos, i = 1, length = getLength();

    printf("Enter position : ");
    scanf("%d", &pos);

    if(pos < 1 || pos > length){
        printf("Invalid position");
    }

    temp = head;

    while(i < pos){
        temp = temp -> next;
        i++;
    }

    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;

    if(temp -> next == head){
        tail = temp -> prev;

        free(temp);
    }else{
        free(temp);
    }

    printf("Data after deletion at the specific position : ");
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

int getLength() {
    if(head == NULL) {
        return 0;
    }

    struct node *temp = head;
    int count = 0;

    do {
        count++;
        temp = temp->next;
    } while(temp != head);

    return count;
}
