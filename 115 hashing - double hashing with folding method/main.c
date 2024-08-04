#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define PART_SIZE 2 // Number of digits in each part for folding

// Function prototypes
void insert(int hashTable[], int key);
void delete(int hashTable[], int key);
void display(int hashTable[]);
int hashFunction1(int key);
int hashFunction2(int key);
int foldingMethod(int key);
int doubleHash(int key, int i);

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

// Function to insert a key into the hash table using double hashing
void insert(int hashTable[], int key) {
    int index = hashFunction1(key); // Calculate the index using the first hash function
    int i = 0;
    bool inserted = false;

    // Double hashing to find an empty slot
    while (!inserted) {
        int newIndex = doubleHash(key, i);
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

// Function to delete a key from the hash table using double hashing
void delete(int hashTable[], int key) {
    int index = hashFunction1(key); // Calculate the index using the first hash function
    int i = 0;
    bool found = false;

    // Double hashing to find the key
    while (hashTable[doubleHash(key, i)] != -1) {
        int newIndex = doubleHash(key, i);
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

// First hash function using folding method
int hashFunction1(int key) {
    int foldedKey = foldingMethod(key);
    return foldedKey % TABLE_SIZE;
}

// Second hash function for double hashing
int hashFunction2(int key) {
    return 1 + (foldingMethod(key) % (TABLE_SIZE - 1)); // Avoid 0 to prevent infinite loops
}

// Folding method to compute hash value
int foldingMethod(int key) {
    int sum = 0;
    int part;
    while (key > 0) {
        part = key % 10000;  // Take last 4 digits
        sum += part;
        key /= 10000;        // Remove last 4 digits
    }
    return sum;
}

// Double hashing function
int doubleHash(int key, int i) {
    return (hashFunction1(key) + i * hashFunction2(key)) % TABLE_SIZE;
}
