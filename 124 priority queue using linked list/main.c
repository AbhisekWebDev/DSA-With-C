#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
struct Node {
    int value;     // The value of the element
    int priority;  // The priority of the element
    struct Node* next; // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int value, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into the priority queue
void insert(struct Node** head, int value, int priority) {
    struct Node* newNode = createNode(value, priority);

    // If the list is empty or the new node has a higher priority than the head
    if (*head == NULL || (*head)->priority > priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        // Traverse the list and find the correct position to insert the new node
        struct Node* temp = *head;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    printf("Inserted value: %d with priority: %d\n", value, priority);
}

// Function to delete the highest priority element
void delete(struct Node** head) {
    if (*head == NULL) {
        printf("Priority Queue is empty!\n");
        return;
    }

    // The head node has the highest priority, so we remove it
    struct Node* temp = *head;
    *head = (*head)->next;
    printf("Deleted value: %d with priority: %d\n", temp->value, temp->priority);
    free(temp); // Free the memory used by the deleted node
}

// Function to display the priority queue
void display(struct Node* head) {
    if (head == NULL) {
        printf("Priority Queue is empty!\n");
        return;
    }

    printf("Priority Queue:\n");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("Value: %d, Priority: %d\n", temp->value, temp->priority);
        temp = temp->next;
    }
}

// Main function to demonstrate priority queue operations
int main() {
    struct Node* pq = NULL; // Initialize an empty priority queue (linked list)
    int choice, value, priority;

    while (1) {
        printf("\nPriority Queue Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the priority: ");
                scanf("%d", &priority);
                insert(&pq, value, priority);
                break;
            case 2:
                delete(&pq);
                break;
            case 3:
                display(pq);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
