#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int items[MAX];
    int front;
    int rear;
} CircularQueue;

void init(CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(CircularQueue* q) {
    return (q->front == -1);
}

bool isFull(CircularQueue* q) {
    return ((q->rear + 1) % MAX == q->front);
}

void enqueue(CircularQueue* q, int val) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d (Queue is full)\n", val);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear] = val;
    printf("Enqueued: %d (front=%d, rear=%d)\n", val, q->front, q->rear);
}

int dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Queue is empty\n");
        return -1;
    }
    int val = q->items[q->front];
    if (q->front == q->rear) {
        // Last remaining element dequeued
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return val;
}

int peekFront(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

void display(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Circular Queue elements: ");
    int i = q->front;
    while (true) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularQueue q;
    init(&q);

    printf("--- Testing Circular Queue using Array (Capacity: %d) ---\n\n", MAX);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    display(&q);

    // Full test
    enqueue(&q, 60);

    printf("\nDequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    display(&q);

    printf("\n--- Enqueueing after dequeue (Demonstrating Wraparound) ---\n");
    enqueue(&q, 60);
    enqueue(&q, 70);

    display(&q);
    printf("Front: %d\n", peekFront(&q));

    return 0;
}
