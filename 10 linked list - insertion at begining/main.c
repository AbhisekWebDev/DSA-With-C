#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct node{

        int data;
        struct node *next;
    };

    struct node *head = 0, *newNode, *temp;

    int choice = 1, count = 0;

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

    temp = head;

    printf("Entered data: \n");

    while(temp != 0){

        printf("%d ", temp -> data);

        temp = temp -> next;
    }

    // Insert a new node at the beginning

    newNode = (struct node*)malloc(sizeof(struct node));

    printf("\nEnter data at the beginning: \n");
    scanf("%d", &newNode->data);

    newNode->next = head;
    head = newNode;

    temp = head;

    printf("Entered data after insertion at the beginning: \n");

    while(temp != 0){

        printf("%d ", temp->data);

        temp = temp->next;

        count++;
    }

    printf("\nTotal number of nodes: %d\n", count);

    return 0;
}



