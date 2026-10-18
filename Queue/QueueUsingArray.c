#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int items[MAX];
    int front;
    int rear;
} LinearQueue;

void init(LinearQueue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(LinearQueue* q) {
    return (q->front == -1 || q->front > q->rear);
}

bool isFull(LinearQueue* q) {
    return (q->rear == MAX - 1);
}

void enqueue(LinearQueue* q, int val) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d\n", val);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++(q->rear)] = val;
    printf("Enqueued: %d\n", val);
}

int dequeue(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Queue is empty\n");
        return -1;
    }
    int val = q->items[q->front++];
    if (q->front > q->rear) {
        // Reset pointers when queue becomes empty
        q->front = -1;
        q->rear = -1;
    }
    return val;
}

int getFront(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

void display(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main() {
    LinearQueue q;
    init(&q);

    printf("--- Testing Linear Queue using Array ---\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    // Overflow check
    enqueue(&q, 60);

    display(&q);
    printf("Front element: %d\n", getFront(&q));

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    display(&q);
    printf("Is empty? %s\n", isEmpty(&q) ? "Yes" : "No");
    printf("Is full? %s\n", isFull(&q) ? "Yes" : "No");

    return 0;
}
