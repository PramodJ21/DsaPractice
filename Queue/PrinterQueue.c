#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_JOBS 20

typedef struct {
    int jobId;
    char docName[64];
    int pages;
} PrintJob;

typedef struct {
    PrintJob jobs[MAX_JOBS];
    int front;
    int rear;
} PrinterQueue;

void init(PrinterQueue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(PrinterQueue* q) {
    return (q->front == -1 || q->front > q->rear);
}

bool isFull(PrinterQueue* q) {
    return (q->rear == MAX_JOBS - 1);
}

void addJob(PrinterQueue* q, int id, const char* name, int pages) {
    if (isFull(q)) {
        printf("Printer spool full! Cannot add job %d\n", id);
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->jobs[q->rear].jobId = id;
    strncpy(q->jobs[q->rear].docName, name, 63);
    q->jobs[q->rear].docName[63] = '\0';
    q->jobs[q->rear].pages = pages;
    printf("[Added Job #%d] \"%s\" (%d pages)\n", id, name, pages);
}

void processJob(PrinterQueue* q) {
    if (isEmpty(q)) {
        printf("No print jobs waiting in printer queue.\n");
        return;
    }
    PrintJob current = q->jobs[q->front++];
    printf("--> [PRINTED] Job #%d: \"%s\" (%d pages) completed successfully.\n", 
           current.jobId, current.docName, current.pages);

    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
}

void displayRemainingJobs(PrinterQueue* q) {
    if (isEmpty(q)) {
        printf("Printer Queue Status: No pending jobs.\n");
        return;
    }
    printf("\n--- Pending Print Jobs (FIFO) ---\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("  Position %d -> Job #%d: \"%s\" (%d pages)\n", 
               (i - q->front + 1), q->jobs[i].jobId, q->jobs[i].docName, q->jobs[i].pages);
    }
    printf("---------------------------------\n\n");
}

int main() {
    PrinterQueue pq;
    init(&pq);

    printf("--- Printer Spooler Simulation ---\n\n");
    addJob(&pq, 101, "MSc_Thesis.pdf", 45);
    addJob(&pq, 102, "Resume_Pramod.pdf", 2);
    addJob(&pq, 103, "DSA_Assignment.docx", 12);
    addJob(&pq, 104, "Lab_Report.pdf", 8);

    displayRemainingJobs(&pq);

    processJob(&pq);
    processJob(&pq);

    displayRemainingJobs(&pq);

    addJob(&pq, 105, "Tickets.pdf", 3);
    displayRemainingJobs(&pq);

    processJob(&pq);
    processJob(&pq);
    processJob(&pq);
    processJob(&pq); // Underflow test

    return 0;
}
