#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a Huffman tree node
typedef struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
} Node;

// Define the structure for a min heap (priority queue)
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    Node **array;
} MinHeap;

// Create a new node with given character and frequency
Node* create_node(char data, unsigned freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Create a min heap with given capacity
MinHeap* create_min_heap(unsigned capacity) {
    MinHeap* min_heap = (MinHeap*)malloc(sizeof(MinHeap));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = (Node**)malloc(min_heap->capacity * sizeof(Node*));
    return min_heap;
}

// Swap two nodes
void swap_nodes(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Heapify the min heap
void min_heapify(MinHeap* min_heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < min_heap->size && min_heap->array[left]->freq < min_heap->array[smallest]->freq)
        smallest = left;

    if (right < min_heap->size && min_heap->array[right]->freq < min_heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap_nodes(&min_heap->array[smallest], &min_heap->array[idx]);
        min_heapify(min_heap, smallest);
    }
}

// Check if the size of the heap is one
int is_size_one(MinHeap* min_heap) {
    return (min_heap->size == 1);
}

// Extract the minimum value node from the heap
Node* extract_min(MinHeap* min_heap) {
    Node* temp = min_heap->array[0];
    min_heap->array[0] = min_heap->array[min_heap->size - 1];
    --min_heap->size;
    min_heapify(min_heap, 0);
    return temp;
}

// Insert a new node to the min heap
void insert_min_heap(MinHeap* min_heap, Node* node) {
    ++min_heap->size;
    int i = min_heap->size - 1;

    while (i && node->freq < min_heap->array[(i - 1) / 2]->freq) {
        min_heap->array[i] = min_heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    min_heap->array[i] = node;
}

// Build the min heap
void build_min_heap(MinHeap* min_heap) {
    int n = min_heap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        min_heapify(min_heap, i);
}

// Create and build a min heap
MinHeap* create_and_build_min_heap(char data[], int freq[], int size) {
    MinHeap* min_heap = create_min_heap(size);
    for (int i = 0; i < size; ++i)
        min_heap->array[i] = create_node(data[i], freq[i]);
    min_heap->size = size;
    build_min_heap(min_heap);
    return min_heap;
}

// Build the Huffman tree
Node* build_huffman_tree(char data[], int freq[], int size) {
    Node *left, *right, *top;
    MinHeap* min_heap = create_and_build_min_heap(data, freq, size);

    while (!is_size_one(min_heap)) {
        left = extract_min(min_heap);
        right = extract_min(min_heap);
        top = create_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert_min_heap(min_heap, top);
    }
    return extract_min(min_heap);
}

// Print the Huffman codes
void print_codes(Node* root, int arr[], int top, char codes[128][128]) {
    if (root->left) {
        arr[top] = 0;
        print_codes(root->left, arr, top + 1, codes);
    }

    if (root->right) {
        arr[top] = 1;
        print_codes(root->right, arr, top + 1, codes);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
            codes[root->data][i] = arr[i] + '0';
        }
        codes[root->data][top] = '\0';
        printf("\n");
    }
}

// Build and print the Huffman codes
void huffman_codes(char data[], int freq[], int size, char codes[128][128]) {
    Node* root = build_huffman_tree(data, freq, size);
    int arr[100], top = 0;
    print_codes(root, arr, top, codes);
}

// Encode the input string
void encode(char input[], char codes[128][128], char encoded[]) {
    for (int i = 0; i < strlen(input); i++) {
        strcat(encoded, codes[input[i]]);
    }
}

// Decode the encoded string
void decode(Node* root, char encoded[], char decoded[]) {
    Node* current = root;
    int j = 0;
    for (int i = 0; i < strlen(encoded); i++) {
        if (encoded[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!(current->left) && !(current->right)) {
            decoded[j++] = current->data;
            current = root;
        }
    }
    decoded[j] = '\0';
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(data) / sizeof(data[0]);

    printf("Character | Huffman Code\n");
    printf("------------------------\n");

    char codes[128][128] = {0};  // Huffman codes for each character
    huffman_codes(data, freq, size, codes);

    char input[] = "abcdef";
    char encoded[1000] = "";
    encode(input, codes, encoded);
    printf("\nEncoded message: %s\n", encoded);

    Node* root = build_huffman_tree(data, freq, size);  // Build the Huffman tree again for decoding
    char decoded[1000] = "";
    decode(root, encoded, decoded);
    printf("Decoded message: %s\n", decoded);

    return 0;
}
