#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isQueueEmpty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, int val) {
    if (q->size == MAX) return;
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = val;
    q->size++;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    int val = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return val;
}

void displayQueue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int count = q->size;
    int idx = q->front;
    while (count--) {
        printf("%d ", q->items[idx]);
        idx = (idx + 1) % MAX;
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

void push(Stack* s, int val) {
    s->items[++(s->top)] = val;
}

int pop(Stack* s) {
    return s->items[(s->top)--];
}

// Interleave first half of queue with second half
void interleaveQueue(Queue* q) {
    if (q->size % 2 != 0) {
        printf("Queue has odd number of elements. Interleaving requires even length.\n");
        return;
    }

    int halfSize = q->size / 2;
    Stack s;
    initStack(&s);

    // Step 1: Push first half of queue into stack
    for (int i = 0; i < halfSize; i++) {
        push(&s, dequeue(q));
    }

    // Step 2: Enqueue back stack elements into queue
    while (s.top != -1) {
        enqueue(q, pop(&s));
    }

    // Step 3: Dequeue first half elements and enqueue back to rotate them
    for (int i = 0; i < halfSize; i++) {
        enqueue(q, dequeue(q));
    }

    // Step 4: Push first half into stack again (now reversed in order)
    for (int i = 0; i < halfSize; i++) {
        push(&s, dequeue(q));
    }

    // Step 5: Interleave one from stack, one from queue
    while (s.top != -1) {
        enqueue(q, pop(&s));
        enqueue(q, dequeue(q));
    }
}

int main() {
    Queue q;
    initQueue(&q);

    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        enqueue(&q, arr[i]);
    }

    printf("Original Queue: ");
    displayQueue(&q);

    interleaveQueue(&q);

    printf("Interleaved Queue: ");
    displayQueue(&q);

    return 0;
}
