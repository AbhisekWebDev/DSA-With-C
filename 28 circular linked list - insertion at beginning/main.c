#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
} *head = NULL, *newNode, *temp, *tail = NULL;

int choice = 1;

int main() {
    create();
    display();
    insertAtBeginning();
    display();
    return 0;
}

void create() {
    while(choice) {
        newNode = (struct node*)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if(head == NULL) {
            head = newNode;
            tail = newNode;
            newNode->next = head; // Point to itself for circular linked list
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // Maintain circular linked list
        }

        printf("0 to abort & 1 to continue (0, 1): ");
        scanf("%d", &choice);
    }
}

void insertAtBeginning() {
    newNode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data at the beginning: ");
    scanf("%d", &newNode->data);

    if(head == NULL) {
        head = newNode;
        tail = newNode;
        newNode->next = head; // Point to itself for circular linked list
    } else {
        newNode->next = head;
        head = newNode;
        tail->next = head; // Maintain circular linked list
    }
}

void display() {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    temp = head;
    int count = 0; // Reset count for each display
    printf("Entered data: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
        count++;
    } while(temp != head);

    printf("\nTotal number of nodes: %d\n", count);
}
