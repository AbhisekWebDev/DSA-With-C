#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the size of the hash table
#define TABLE_SIZE 10

// Function prototypes
void insert(int hashTable[], int key);
void delete(int hashTable[], int key);
void display(int hashTable[]);
int hashFunction(int key);

int main() {
    // Initialize the hash table with -1 to indicate empty slots
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    // Insert some keys into the hash table
    insert(hashTable, 23);
    insert(hashTable, 43);
    insert(hashTable, 13);
    insert(hashTable, 27);
    insert(hashTable, 53);

    // Display the hash table
    printf("Hash table after insertion:\n");
    display(hashTable);

    // Delete a key from the hash table
    delete(hashTable, 13);

    // Display the hash table after deletion
    printf("Hash table after deletion:\n");
    display(hashTable);

    return 0;
}

// Function to insert a key into the hash table using linear probing
void insert(int hashTable[], int key) {
    int index = hashFunction(key); // Calculate the index using the division method
    int originalIndex = index;
    bool inserted = false;

    // Linear probing to find an empty slot
    while (!inserted) {
        if (hashTable[index] == -1) {
            hashTable[index] = key;
            inserted = true;
        } else {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                printf("Hash table is full, cannot insert key %d\n", key);
                return;
            }
        }
    }
}

// Function to delete a key from the hash table using linear probing
void delete(int hashTable[], int key) {
    int index = hashFunction(key); // Calculate the index using the division method
    int originalIndex = index;
    bool found = false;

    // Linear probing to find the key
    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            hashTable[index] = -1;
            found = true;
            break;
        } else {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                break;
            }
        }
    }

    if (!found) {
        printf("Key %d not found in the hash table\n", key);
    }
}

// Function to display the hash table
void display(int hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != -1) {
            printf("hashTable[%d]: %d\n", i, hashTable[i]);
        } else {
            printf("hashTable[%d]: NULL\n", i);
        }
    }
}

// Hash function to calculate the index using the division method
int hashFunction(int key) {
    return key % TABLE_SIZE;
}
