#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Maximum size of the priority queue

// Structure to represent an element in the priority queue
struct Element {
    int value;   // The value/data of the element
    int priority; // The priority of the element
};

// Priority Queue array and current size
struct Element priorityQueue[MAX];
int size = 0;

// Function to insert an element into the priority queue
void insert(int value, int priority) {
    // Check if the priority queue is full
    if (size == MAX) {
        printf("Priority Queue is full!\n");
        return;
    }

    // Insert the new element into the priority queue
    priorityQueue[size].value = value;
    priorityQueue[size].priority = priority;
    size++;

    printf("Inserted value: %d with priority: %d\n", value, priority);
}

// Function to find the highest priority element and remove it from the queue
void delete() {
    if (size == 0) {
        printf("Priority Queue is empty!\n");
        return;
    }

    // Find the element with the highest priority
    int highestPriorityIndex = 0;
    for (int i = 1; i < size; i++) {
        // If the current element has a higher priority, update the highest priority index
        if (priorityQueue[i].priority < priorityQueue[highestPriorityIndex].priority) {
            highestPriorityIndex = i;
        }
    }

    // Remove the element with the highest priority by shifting the remaining elements
    printf("Deleted value: %d with priority: %d\n", priorityQueue[highestPriorityIndex].value, priorityQueue[highestPriorityIndex].priority);

    for (int i = highestPriorityIndex; i < size - 1; i++) {
        priorityQueue[i] = priorityQueue[i + 1];
    }

    size--; // Reduce the size of the queue
}

// Function to display the elements in the priority queue
void display() {
    if (size == 0) {
        printf("Priority Queue is empty!\n");
        return;
    }

    printf("Priority Queue: \n");
    for (int i = 0; i < size; i++) {
        printf("Value: %d, Priority: %d\n", priorityQueue[i].value, priorityQueue[i].priority);
    }
}

// Main function to demonstrate the Priority Queue operations
int main() {
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
                insert(value, priority);
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
