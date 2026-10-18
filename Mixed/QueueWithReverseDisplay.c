#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct {
    struct Node* front;
    struct Node* rear;
} LinkedQueue;

void initQueue(LinkedQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

bool isEmpty(LinkedQueue* q) {
    return q->front == NULL;
}

void enqueue(LinkedQueue* q, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(LinkedQueue* q) {
    if (isEmpty(q)) return -1;
    struct Node* temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return val;
}

// Display elements in normal FIFO order
void displayNormal(LinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Normal Queue (front to rear): ");
    struct Node* curr = q->front;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Recursive helper for non-destructive reverse display
void displayReverseHelper(struct Node* node) {
    if (node == NULL) return;
    displayReverseHelper(node->next);
    printf("%d ", node->data);
}

// Display elements in reverse order without modifying queue
void displayReverse(LinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Reverse Queue (rear to front): ");
    displayReverseHelper(q->front);
    printf("\n");
}

int main() {
    LinkedQueue q;
    initQueue(&q);

    int items[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) enqueue(&q, items[i]);

    printf("--- Queue with Non-Destructive Reverse Display ---\n\n");
    displayNormal(&q);
    displayReverse(&q);

    // Verify queue remains completely unchanged
    printf("\nVerifying queue state after reverse display:\n");
    displayNormal(&q);
    printf("Dequeuing first element: %d\n", dequeue(&q));
    displayNormal(&q);
    displayReverse(&q);

    return 0;
}
