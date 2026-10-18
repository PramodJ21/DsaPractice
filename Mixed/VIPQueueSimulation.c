#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 50

typedef struct {
    int id;
    char name[64];
    bool isVIP;
} Customer;

typedef struct {
    Customer items[MAX_LINE];
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

void enqueue(Queue* q, Customer c) {
    if (q->count == MAX_LINE) return;
    q->rear = (q->rear + 1) % MAX_LINE;
    q->items[q->rear] = c;
    q->count++;
}

Customer dequeue(Queue* q) {
    Customer c = q->items[q->front];
    q->front = (q->front + 1) % MAX_LINE;
    q->count--;
    return c;
}

typedef struct {
    Queue vipQueue;
    Queue regularQueue;
    int nextId;
} BankServiceSystem;

void initSystem(BankServiceSystem* sys) {
    initQueue(&sys->vipQueue);
    initQueue(&sys->regularQueue);
    sys->nextId = 1;
}

// Add customer to appropriate queue
void arrive(BankServiceSystem* sys, const char* name, bool isVIP) {
    Customer c;
    c.id = sys->nextId++;
    strncpy(c.name, name, 63);
    c.name[63] = '\0';
    c.isVIP = isVIP;

    if (isVIP) {
        enqueue(&sys->vipQueue, c);
        printf("[ARRIVAL - VIP] #%d %s joined the VIP Priority Line.\n", c.id, c.name);
    } else {
        enqueue(&sys->regularQueue, c);
        printf("[ARRIVAL - REG] #%d %s joined the Regular Line.\n", c.id, c.name);
    }
}

// Serve customer: VIPs are strictly served first before regular customers
void serve(BankServiceSystem* sys) {
    if (!isEmpty(&sys->vipQueue)) {
        Customer c = dequeue(&sys->vipQueue);
        printf("--> [SERVED VIP] Customer #%d (%s) served from VIP line.\n", c.id, c.name);
    } else if (!isEmpty(&sys->regularQueue)) {
        Customer c = dequeue(&sys->regularQueue);
        printf("--> [SERVED REG] Customer #%d (%s) served from Regular line.\n", c.id, c.name);
    } else {
        printf("--> [IDLE] No customers waiting in either line.\n");
    }
}

void displayLines(BankServiceSystem* sys) {
    printf("\n=== Current Waiting Status ===\n");
    printf("  VIP Line (%d waiting): ", sys->vipQueue.count);
    int idx = sys->vipQueue.front;
    for (int i = 0; i < sys->vipQueue.count; i++) {
        printf("[#%d %s] ", sys->vipQueue.items[idx].id, sys->vipQueue.items[idx].name);
        idx = (idx + 1) % MAX_LINE;
    }
    printf("\n");

    printf("  Regular Line (%d waiting): ", sys->regularQueue.count);
    idx = sys->regularQueue.front;
    for (int i = 0; i < sys->regularQueue.count; i++) {
        printf("[#%d %s] ", sys->regularQueue.items[idx].id, sys->regularQueue.items[idx].name);
        idx = (idx + 1) % MAX_LINE;
    }
    printf("\n==============================\n\n");
}

int main() {
    BankServiceSystem bank;
    initSystem(&bank);

    printf("--- Priority Customer Simulation (VIP vs Regular Queues) ---\n\n");
    // Regular customers arrive first
    arrive(&bank, "John Doe", false);
    arrive(&bank, "Jane Smith", false);

    // VIP customer arrives later
    arrive(&bank, "Senator Armstrong", true);

    displayLines(&bank);

    // Serve: VIP Armstrong served before John Doe despite John arriving earlier
    serve(&bank);
    displayLines(&bank);

    // More arrivals
    arrive(&bank, "Mark Brown", false);
    arrive(&bank, "CEO Stark", true);
    displayLines(&bank);

    // Serve remaining
    serve(&bank); // Serves CEO Stark (VIP)
    serve(&bank); // Serves John Doe (Regular)
    serve(&bank); // Serves Jane Smith (Regular)
    serve(&bank); // Serves Mark Brown (Regular)
    serve(&bank); // Empty

    return 0;
}
