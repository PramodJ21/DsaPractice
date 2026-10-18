#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

bool isEmpty(Queue* q) {
    return q->count == 0;
}

void enqueue(Queue* q, int val) {
    if (q->count == MAX) {
        printf("  [OVERFLOW] Queue full, cannot enqueue %d\n", val);
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = val;
    q->count++;
    printf("  [ENQUEUE] Enqueued %d (Queue Size: %d)\n", val, q->count);
}

int dequeue(Queue* q, bool* isUnderflow) {
    if (isEmpty(q)) {
        *isUnderflow = true;
        printf("  [UNDERFLOW ERROR!] Dequeue failed: Queue is currently empty!\n");
        return -1;
    }
    *isUnderflow = false;
    int val = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    printf("  [DEQUEUE] Dequeued %d (Queue Size: %d)\n", val, q->count);
    return val;
}

void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty []\n");
        return;
    }
    printf("Queue contents [ ");
    int idx = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->items[idx]);
        idx = (idx + 1) % MAX;
    }
    printf("]\n");
}

typedef enum { OP_ENQUEUE, OP_DEQUEUE } OpType;

typedef struct {
    OpType type;
    int val; // Only used for OP_ENQUEUE
} Operation;

void runSimulation(Operation ops[], int n) {
    Queue q;
    initQueue(&q);
    int underflowCount = 0;

    printf("Starting Queue Operations Trace (%d operations):\n", n);
    printf("---------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("Op #%2d: ", i + 1);
        if (ops[i].type == OP_ENQUEUE) {
            enqueue(&q, ops[i].val);
        } else {
            bool underflow = false;
            dequeue(&q, &underflow);
            if (underflow) underflowCount++;
        }
    }

    printf("---------------------------------------------------\n");
    printf("Simulation Summary:\n");
    printf("  Total Operations Executed : %d\n", n);
    printf("  Total Underflows Detected : %d\n", underflowCount);
    printf("  Final Queue Status        : ");
    displayQueue(&q);
    printf("\n");
}

int main() {
    printf("--- Queue Operation Sequence & Underflow Analysis ---\n\n");

    // Sequence with intentional underflow attempts
    Operation sequence[] = {
        {OP_ENQUEUE, 10},
        {OP_ENQUEUE, 20},
        {OP_DEQUEUE, 0},
        {OP_ENQUEUE, 30},
        {OP_DEQUEUE, 0},
        {OP_DEQUEUE, 0},
        {OP_DEQUEUE, 0}, // Underflow 1
        {OP_DEQUEUE, 0}, // Underflow 2
        {OP_ENQUEUE, 40},
        {OP_ENQUEUE, 50},
        {OP_ENQUEUE, 60},
        {OP_DEQUEUE, 0},
        {OP_ENQUEUE, 70}
    };
    int n = sizeof(sequence) / sizeof(sequence[0]);

    runSimulation(sequence, n);

    return 0;
}
