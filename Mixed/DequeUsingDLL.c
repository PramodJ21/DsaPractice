#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct {
    struct Node* front;
    struct Node* rear;
} LinkedDeque;

void initDeque(LinkedDeque* dq) {
    dq->front = NULL;
    dq->rear = NULL;
}

bool isEmpty(LinkedDeque* dq) {
    return dq->front == NULL;
}

// Insert at front - O(1)
void insertFront(LinkedDeque* dq, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = dq->front;

    if (isEmpty(dq)) {
        dq->rear = newNode;
    } else {
        dq->front->prev = newNode;
    }
    dq->front = newNode;
    printf("Inserted at FRONT: %d\n", val);
}

// Insert at rear - O(1)
void insertRear(LinkedDeque* dq, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = dq->rear;

    if (isEmpty(dq)) {
        dq->front = newNode;
    } else {
        dq->rear->next = newNode;
    }
    dq->rear = newNode;
    printf("Inserted at REAR : %d\n", val);
}

// Delete from front - O(1)
int deleteFront(LinkedDeque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from front.\n");
        return -1;
    }
    struct Node* temp = dq->front;
    int val = temp->data;

    dq->front = dq->front->next;
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    free(temp);
    return val;
}

// Delete from rear - O(1)
int deleteRear(LinkedDeque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from rear.\n");
        return -1;
    }
    struct Node* temp = dq->rear;
    int val = temp->data;

    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    free(temp);
    return val;
}

int getFront(LinkedDeque* dq) {
    if (isEmpty(dq)) return -1;
    return dq->front->data;
}

int getRear(LinkedDeque* dq) {
    if (isEmpty(dq)) return -1;
    return dq->rear->data;
}

void display(LinkedDeque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque (front to rear): ");
    struct Node* curr = dq->front;
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->next != NULL) printf("<-> ");
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    LinkedDeque dq;
    initDeque(&dq);

    printf("--- Deque Implementation using Doubly Linked List ---\n\n");
    insertRear(&dq, 20);
    insertRear(&dq, 30);
    insertFront(&dq, 10);
    insertFront(&dq, 5);
    insertRear(&dq, 40);

    display(&dq);
    printf("Front: %d, Rear: %d\n\n", getFront(&dq), getRear(&dq));

    printf("Deleted from front: %d\n", deleteFront(&dq));
    display(&dq);

    printf("Deleted from rear : %d\n", deleteRear(&dq));
    display(&dq);

    printf("Deleted from rear : %d\n", deleteRear(&dq));
    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from front: %d\n", deleteFront(&dq));
    deleteFront(&dq); // Underflow test

    return 0;
}
