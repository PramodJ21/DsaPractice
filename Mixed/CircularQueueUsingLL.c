#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct {
    struct Node* rear; // rear->next is always front in a circular linked list
} CircularLinkedQueue;

void initQueue(CircularLinkedQueue* q) {
    q->rear = NULL;
}

bool isEmpty(CircularLinkedQueue* q) {
    return q->rear == NULL;
}

// Enqueue element at rear - O(1)
void enqueue(CircularLinkedQueue* q, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;

    if (isEmpty(q)) {
        newNode->next = newNode; // Points to itself
        q->rear = newNode;
    } else {
        newNode->next = q->rear->next; // Point to front
        q->rear->next = newNode;
        q->rear = newNode;             // Advance rear
    }
    printf("Enqueued: %d\n", val);
}

// Dequeue element from front (rear->next) - O(1)
int dequeue(CircularLinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Queue is empty.\n");
        return -1;
    }

    struct Node* front = q->rear->next;
    int val = front->data;

    if (q->rear == front) {
        // Only one element in the queue
        free(front);
        q->rear = NULL;
    } else {
        q->rear->next = front->next;
        free(front);
    }
    return val;
}

// Get front element
int peekFront(CircularLinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->rear->next->data;
}

// Display circular linked queue elements from front to rear
void display(CircularLinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Circular Linked Queue (front to rear): ");
    struct Node* curr = q->rear->next; // Front
    do {
        printf("%d ", curr->data);
        curr = curr->next;
    } while (curr != q->rear->next);
    printf("\n");
}

int main() {
    CircularLinkedQueue q;
    initQueue(&q);

    printf("--- Circular Queue using Linked List ---\n\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    display(&q);
    printf("Front: %d\n", peekFront(&q));

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    display(&q);

    enqueue(&q, 50);
    enqueue(&q, 60);
    display(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    dequeue(&q); // Underflow test

    return 0;
}
