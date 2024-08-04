#include <stdio.h>
#include <stdlib.h>

// Define the size of the hash table
#define TABLE_SIZE 10

// Define a node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
void insert(Node* hashTable[], int key);
void delete(Node* hashTable[], int key);
void display(Node* hashTable[]);
int hashFunction(int key);

int main() {
    // Initialize the hash table with NULL
    Node* hashTable[TABLE_SIZE] = {NULL};

    // Insert some keys into the hash table
    insert(hashTable, 10);
    insert(hashTable, 20);
    insert(hashTable, 15);
    insert(hashTable, 5);
    insert(hashTable, 30);
    insert(hashTable, 25);

    // Display the hash table
    printf("Hash table after insertion:\n");
    display(hashTable);

    // Delete a key from the hash table
    delete(hashTable, 20);

    // Display the hash table after deletion
    printf("Hash table after deletion:\n");
    display(hashTable);

    return 0;
}

// Function to insert a key into the hash table
void insert(Node* hashTable[], int key) {
    int index = hashFunction(key);

    // Create a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;

    // Insert the new node at the beginning of the linked list at the calculated index
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

// Function to delete a key from the hash table
void delete(Node* hashTable[], int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;

    // Traverse the linked list at the calculated index
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key is not found
    if (temp == NULL) {
        printf("Key %d not found in the hash table\n", key);
        return;
    }

    // If key is found, delete the node
    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
}

// Function to display the hash table
void display(Node* hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("hashTable[%d]: ", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Hash function to calculate the index
int hashFunction(int key) {
    return key % TABLE_SIZE;
}
