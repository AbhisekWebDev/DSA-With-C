#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// Function prototypes
void insert(int hashTable[], int key);
void delete(int hashTable[], int key);
void display(int hashTable[]);
int hashFunction(int key);
int quadraticProbe(int hashTable[], int index, int i);

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
    insert(hashTable, 18);

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

// Function to insert a key into the hash table using quadratic probing
void insert(int hashTable[], int key) {
    int index = hashFunction(key); // Calculate the index using the division method
    int originalIndex = index;
    bool inserted = false;
    int i = 0;

    // Quadratic probing to find an empty slot
    while (!inserted) {
        int newIndex = quadraticProbe(hashTable, index, i);
        if (hashTable[newIndex] == -1) {
            hashTable[newIndex] = key;
            inserted = true;
        } else {
            i++;
            if (i == TABLE_SIZE) {
                printf("Hash table is full, cannot insert key %d\n", key);
                return;
            }
        }
    }
}

// Function to delete a key from the hash table using quadratic probing
void delete(int hashTable[], int key) {
    int index = hashFunction(key); // Calculate the index using the division method
    int originalIndex = index;
    bool found = false;
    int i = 0;

    // Quadratic probing to find the key
    while (hashTable[quadraticProbe(hashTable, index, i)] != -1) {
        int newIndex = quadraticProbe(hashTable, index, i);
        if (hashTable[newIndex] == key) {
            hashTable[newIndex] = -1;
            found = true;
            break;
        } else {
            i++;
            if (i == TABLE_SIZE) {
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

// Function to calculate the index using quadratic probing
int quadraticProbe(int hashTable[], int index, int i) {
    return (index + i * i) % TABLE_SIZE;
}
