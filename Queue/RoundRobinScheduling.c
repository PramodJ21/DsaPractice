#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROC 20
#define QUEUE_SIZE 50

typedef struct {
    int pid;
    int burstTime;
    int remainingTime;
    int completionTime;
} Process;

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} CircularQueue;

void initQueue(CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(CircularQueue* q) {
    return q->front == -1;
}

void enqueue(CircularQueue* q, int val) {
    if ((q->rear + 1) % QUEUE_SIZE == q->front) return;
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % QUEUE_SIZE;
    }
    q->items[q->rear] = val;
}

int dequeue(CircularQueue* q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % QUEUE_SIZE;
    }
    return val;
}

void simulateRoundRobin(Process proc[], int n, int quantum) {
    CircularQueue q;
    initQueue(&q);

    // Enqueue all processes in arrival order
    for (int i = 0; i < n; i++) {
        enqueue(&q, i);
    }

    int currentTime = 0;
    int completedCount = 0;
    int completionOrder[MAX_PROC];

    printf("Starting Round-Robin Scheduling (Time Quantum = %d ms)\n", quantum);
    printf("----------------------------------------------------------\n");

    while (!isEmpty(&q)) {
        int idx = dequeue(&q);

        printf("Time %3d ms: Executing Process P%d (Remaining: %d ms) -> ", 
               currentTime, proc[idx].pid, proc[idx].remainingTime);

        if (proc[idx].remainingTime > quantum) {
            currentTime += quantum;
            proc[idx].remainingTime -= quantum;
            printf("ran for %d ms, remaining: %d ms\n", quantum, proc[idx].remainingTime);
            enqueue(&q, idx); // Re-insert into circular queue
        } else {
            currentTime += proc[idx].remainingTime;
            printf("ran for %d ms and COMPLETED at %d ms!\n", proc[idx].remainingTime, currentTime);
            proc[idx].remainingTime = 0;
            proc[idx].completionTime = currentTime;
            completionOrder[completedCount++] = proc[idx].pid;
        }
    }

    printf("\n==========================================================\n");
    printf("All processes completed.\n\n");
    printf("%-10s %-15s %-15s\n", "Process", "Burst Time", "Completion Time");
    printf("-----------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%-9d %-15d %-15d\n", proc[i].pid, proc[i].burstTime, proc[i].completionTime);
    }

    printf("\nCompletion Order: ");
    for (int i = 0; i < completedCount; i++) {
        printf("P%d%s", completionOrder[i], (i == completedCount - 1) ? "" : " -> ");
    }
    printf("\n");
}

int main() {
    Process proc[] = {
        {1, 10, 10, 0},
        {2, 5,  5,  0},
        {3, 8,  8,  0},
        {4, 4,  4,  0}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 3;

    simulateRoundRobin(proc, n, quantum);

    return 0;
}
