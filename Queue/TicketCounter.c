#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CUSTOMERS 30

typedef struct {
    int tokenNo;
    char name[50];
    int ticketCount;
} Customer;

typedef struct {
    Customer queue[MAX_CUSTOMERS];
    int front;
    int rear;
    int nextToken;
} TicketCounter;

void init(TicketCounter* tc) {
    tc->front = -1;
    tc->rear = -1;
    tc->nextToken = 1;
}

bool isEmpty(TicketCounter* tc) {
    return (tc->front == -1 || tc->front > tc->rear);
}

bool isFull(TicketCounter* tc) {
    return (tc->rear == MAX_CUSTOMERS - 1);
}

// New customer arrives and joins queue
void arriveCustomer(TicketCounter* tc, const char* name, int ticketCount) {
    if (isFull(tc)) {
        printf("Waiting line is at maximum capacity! Customer %s turned away.\n", name);
        return;
    }
    if (tc->front == -1) tc->front = 0;
    tc->rear++;
    tc->queue[tc->rear].tokenNo = tc->nextToken++;
    strncpy(tc->queue[tc->rear].name, name, 49);
    tc->queue[tc->rear].name[49] = '\0';
    tc->queue[tc->rear].ticketCount = ticketCount;

    printf("[Arrival] Token #%d: %s joined the queue requesting %d ticket(s).\n", 
           tc->queue[tc->rear].tokenNo, name, ticketCount);
}

// Serve next customer in arrival order
void serveCustomer(TicketCounter* tc) {
    if (isEmpty(tc)) {
        printf("No customers in queue to serve!\n");
        return;
    }
    Customer served = tc->queue[tc->front++];
    printf("--> [SERVED] Token #%d: %s received %d ticket(s) and exited.\n", 
           served.tokenNo, served.name, served.ticketCount);

    if (tc->front > tc->rear) {
        tc->front = -1;
        tc->rear = -1;
    }
}

// Display current waiting line
void displayWaitingList(TicketCounter* tc) {
    if (isEmpty(tc)) {
        printf("Ticket Counter Queue: Currently empty.\n\n");
        return;
    }
    printf("\n=== Current Ticket Counter Waiting Line ===\n");
    for (int i = tc->front; i <= tc->rear; i++) {
        printf("  Queue Spot %d | Token #%d: %-12s | Tickets: %d\n", 
               (i - tc->front + 1), tc->queue[i].tokenNo, tc->queue[i].name, tc->queue[i].ticketCount);
    }
    printf("===========================================\n\n");
}

int main() {
    TicketCounter counter;
    init(&counter);

    printf("--- Ticket Counter Simulation ---\n\n");
    arriveCustomer(&counter, "Alice", 2);
    arriveCustomer(&counter, "Bob", 4);
    arriveCustomer(&counter, "Charlie", 1);
    arriveCustomer(&counter, "Diana", 3);

    displayWaitingList(&counter);

    serveCustomer(&counter);
    serveCustomer(&counter);

    displayWaitingList(&counter);

    arriveCustomer(&counter, "Edward", 2);
    displayWaitingList(&counter);

    serveCustomer(&counter);
    serveCustomer(&counter);
    serveCustomer(&counter);
    serveCustomer(&counter); // Empty check

    return 0;
}
