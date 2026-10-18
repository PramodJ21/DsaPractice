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

void init(LinkedQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

bool isEmpty(LinkedQueue* q) {
    return (q->front == NULL);
}

// Enqueue at rear - O(1)
void enqueue(LinkedQueue* q, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Heap Overflow! Cannot allocate memory\n");
        return;
    }
    newNode->data = val;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued: %d\n", val);
}

// Dequeue from front - O(1)
int dequeue(LinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Queue is empty\n");
        return -1;
    }
    struct Node* temp = q->front;
    int val = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return val;
}

int peekFront(LinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->front->data;
}

void display(LinkedQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front to rear): ");
    struct Node* curr = q->front;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    LinkedQueue q;
    init(&q);

    printf("--- Testing Queue using Linked List (Front and Rear Pointers) ---\n\n");
    enqueue(&q, 100);
    enqueue(&q, 200);
    enqueue(&q, 300);

    display(&q);
    printf("Front: %d\n", peekFront(&q));

    printf("Dequeued: %d\n", dequeue(&q));
    display(&q);

    enqueue(&q, 400);
    display(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    display(&q);

    return 0;
}
