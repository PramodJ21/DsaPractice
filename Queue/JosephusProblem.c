#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 500

typedef struct {
    int items[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

void initQueue(CircularQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isEmpty(CircularQueue* q) {
    return q->size == 0;
}

void enqueue(CircularQueue* q, int val) {
    if (q->size == MAX) return;
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = val;
    q->size++;
}

int dequeue(CircularQueue* q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return val;
}

// Solve Josephus problem using circular queue simulation
int solveJosephus(int n, int k) {
    CircularQueue q;
    initQueue(&q);

    // Enqueue people numbered 1 to n
    for (int i = 1; i <= n; i++) {
        enqueue(&q, i);
    }

    printf("Simulating Josephus Circle: %d people, eliminate every %d-th person\n", n, k);
    printf("Elimination order: ");

    while (q.size > 1) {
        // Skip k - 1 people by moving them from front to rear
        for (int i = 1; i < k; i++) {
            enqueue(&q, dequeue(&q));
        }
        // Eliminate the k-th person
        int eliminated = dequeue(&q);
        printf("%d ", eliminated);
    }

    int survivor = dequeue(&q);
    printf("\n--> Survivor: Person #%d\n\n", survivor);
    return survivor;
}

int main() {
    solveJosephus(7, 3);
    solveJosephus(5, 2);
    solveJosephus(14, 2);

    return 0;
}
