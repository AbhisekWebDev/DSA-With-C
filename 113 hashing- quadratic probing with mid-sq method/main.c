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
int midSquare(int key);

int main() {
    // Initialize the hash table with -1 to indicate empty slots
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    // Insert some keys into the hash table
    insert(hashTable, 1234);
    insert(hashTable, 2345);
    insert(hashTable, 3456);
    insert(hashTable, 4567);
    insert(hashTable, 5678);

    // Display the hash table
    printf("Hash table after insertion:\n");
    display(hashTable);

    // Delete a key from the hash table
    delete(hashTable, 3456);

    // Display the hash table after deletion
    printf("Hash table after deletion:\n");
    display(hashTable);

    return 0;
}

// Function to insert a key into the hash table using quadratic probing
void insert(int hashTable[], int key) {
    int index = hashFunction(key); // Calculate the index using the mid-square method
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
    int index = hashFunction(key); // Calculate the index using the mid-square method
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

// Hash function to calculate the index using the mid-square method
int hashFunction(int key) {
    int squared = midSquare(key);
    return squared % TABLE_SIZE;
}

// Function to calculate the index using quadratic probing
int quadraticProbe(int hashTable[], int index, int i) {
    return (index + i * i) % TABLE_SIZE;
}

// Function to compute mid-square hash value
int midSquare(int key) {
    int squared = key * key;
    // Extract the middle part of the squared value
    int middle = (squared / 100) % 100; // Assumes we want 2 middle digits
    return middle;
}
