#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int size;
} PriorityQueue;

void init(PriorityQueue* pq) {
    pq->size = 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(PriorityQueue* pq, int index) {
    int parent_index = (index - 1) / 2;
    if (index && pq->data[parent_index] < pq->data[index]) {
        swap(&pq->data[parent_index], &pq->data[index]);
        heapify_up(pq, parent_index);
    }
}

void insert(PriorityQueue* pq, int element) {
    if (pq->size == MAX) {
        printf("Priority Queue is full!\n");
        return;
    }
    pq->data[pq->size++] = element;
    heapify_up(pq, pq->size - 1);
}

void heapify_down(PriorityQueue* pq, int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    if (left_child < pq->size && pq->data[left_child] > pq->data[largest])
        largest = left_child;

    if (right_child < pq->size && pq->data[right_child] > pq->data[largest])
        largest = right_child;

    if (largest != index) {
        swap(&pq->data[index], &pq->data[largest]);
        heapify_down(pq, largest);
    }
}

int extract_max(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    int max_value = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapify_down(pq, 0);
    return max_value;
}

void display(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->data[i]);
    }
    printf("\n");
}

int main() {
    PriorityQueue pq;
    init(&pq);

    insert(&pq, 10);
    insert(&pq, 20);
    insert(&pq, 15);
    insert(&pq, 30);
    insert(&pq, 40);

    printf("Priority Queue: ");
    display(&pq);

    printf("Extracted max: %d\n", extract_max(&pq));
    printf("Priority Queue after extraction: ");
    display(&pq);

    return 0;
}
