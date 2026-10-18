#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isQueueEmpty(Queue* q) {
    return (q->front == -1 || q->front > q->rear);
}

void enqueue(Queue* q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++(q->rear)] = val;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    int val = q->items[q->front++];
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return val;
}

void displayQueue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int val) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = val;
    }
}

int pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

// Reverse queue using an auxiliary stack
void reverseQueue(Queue* q) {
    Stack s;
    initStack(&s);

    // Step 1: Dequeue all elements and push onto stack
    while (!isQueueEmpty(q)) {
        push(&s, dequeue(q));
    }

    // Step 2: Pop all elements from stack and enqueue back to queue
    while (!isStackEmpty(&s)) {
        enqueue(q, pop(&s));
    }
}

int main() {
    Queue q;
    initQueue(&q);

    int elements[] = {10, 20, 30, 40, 50, 60};
    int n = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < n; i++) {
        enqueue(&q, elements[i]);
    }

    printf("Original Queue: ");
    displayQueue(&q);

    reverseQueue(&q);

    printf("Reversed Queue: ");
    displayQueue(&q);

    return 0;
}
