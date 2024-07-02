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

        count++; // isme ye yaha dena hoga kyunki count++ se hi to niche wale if condition me pata chl pyga pos > count h ya nhi
    }

    // Insert a new node at the specific position

    // inserting position

    int pos, i = 1;

    printf("\nEnter position : \n");
    scanf("%d", &pos);

    if (pos < 1 || pos > count) {

        printf("Invalid position\n");
    } else {

        newNode = (struct node*)malloc(sizeof(struct node));

        // inserting the data

        printf("Enter data to store at the specific position: ");
        scanf("%d", &newNode->data);

        temp = head;

        while (i < pos) {
            temp = temp->next;
            i++;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Displaying the nodes

    printf("Entered data after insertion at the specific position: \n");

    temp = head; // Reset temp to head to traverse again

    while(temp != NULL){

        printf("%d ", temp->data);

        temp = temp->next;
    }

    printf("\nTotal number of nodes are : %d ", count + 1);
                                                // yaha count + 1 islye diya h kyunki count++ upr h aur us k bad
                                                // specific position pr node dalne k bad count update nhi ho rha islye
                                                // count + 1 diya h taki update ho k no. of nodes bata pye

    return 0;
}




