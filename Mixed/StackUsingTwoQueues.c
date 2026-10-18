#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

bool isQueueEmpty(Queue* q) {
    return q->count == 0;
}

void enqueue(Queue* q, int val) {
    if (q->count == MAX) return;
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = val;
    q->count++;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    int val = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return val;
}

int getFront(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    return q->items[q->front];
}

typedef struct {
    Queue q1;
    Queue q2;
} StackUsingQueues;

void initStack(StackUsingQueues* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

bool isStackEmpty(StackUsingQueues* s) {
    return isQueueEmpty(&s->q1);
}

// Push element making push costly so pop is O(1)
void push(StackUsingQueues* s, int val) {
    // 1. Enqueue to q2
    enqueue(&s->q2, val);

    // 2. Transfer all from q1 to q2
    while (!isQueueEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // 3. Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    printf("Pushed to stack: %d\n", val);
}

// Pop element - O(1)
int pop(StackUsingQueues* s) {
    if (isStackEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return dequeue(&s->q1);
}

// Peek top element - O(1)
int top(StackUsingQueues* s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return getFront(&s->q1);
}

int main() {
    StackUsingQueues s;
    initStack(&s);

    printf("--- Stack Implementation using Two Queues ---\n\n");
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top: %d\n", top(&s));
    printf("Popped: %d\n", pop(&s));
    printf("Top: %d\n", top(&s));

    push(&s, 40);
    printf("Top: %d\n", top(&s));

    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));
    pop(&s); // Underflow test

    return 0;
}
