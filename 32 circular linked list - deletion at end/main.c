#include <stdio.h>
#include <stdlib.h>

// IN THIS I ONLY MAINTAIN TAIL POINTER (** NO HEAD POINTER **)

struct node {
    int data;
    struct node *next;
} *tail = NULL, *newNode, *temp;

int choice = 1;

int main()
{
    create();
    display();

    deleteAtEnd();
    display();

    return 0;
}

void create() {
    while(choice) {
        newNode = (struct node*)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if(tail == NULL) {
            tail = newNode;
            tail->next = tail; // Point to itself for circular linked list
        } else {
            newNode->next = tail->next; // New node points to head
            tail->next = newNode; // Tail points to new node
            tail = newNode; // Update tail to the new node
        }

        printf("0 to abort & 1 to continue (0, 1): ");
        scanf("%d", &choice);
    }
}

void deleteAtEnd(){

    struct node *currentNode, *prevNode;

    currentNode = tail -> next;

    while(currentNode -> next != tail -> next){
        prevNode = currentNode;
        currentNode = currentNode -> next;
    }

    prevNode -> next = tail -> next;
    tail = prevNode;

    printf("Remaining data after deletion from the end : \n");

    free(currentNode);
}

void display() {
    if(tail == NULL) {
        printf("List is empty\n");
        return;
    }

    temp = tail->next; // Start from head
    int count = 0; // Reset count for each display
    printf("Entered data: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
        count++;
    } while(temp != tail->next);

    printf("\nTotal number of nodes: %d\n", count);
}
