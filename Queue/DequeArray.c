#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int arr[MAX];
    int front;
    int rear;
} Deque;

void init(Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
}

bool isEmpty(Deque* dq) {
    return (dq->front == -1);
}

bool isFull(Deque* dq) {
    return ((dq->front == 0 && dq->rear == MAX - 1) || (dq->front == dq->rear + 1));
}

// Insert element at front
void insertFront(Deque* dq, int val) {
    if (isFull(dq)) {
        printf("Deque Overflow! Cannot insert %d at front\n", val);
        return;
    }
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX - 1; // wrap around
    } else {
        dq->front--;
    }
    dq->arr[dq->front] = val;
    printf("Inserted at front: %d\n", val);
}

// Insert element at rear
void insertRear(Deque* dq, int val) {
    if (isFull(dq)) {
        printf("Deque Overflow! Cannot insert %d at rear\n", val);
        return;
    }
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == MAX - 1) {
        dq->rear = 0; // wrap around
    } else {
        dq->rear++;
    }
    dq->arr[dq->rear] = val;
    printf("Inserted at rear: %d\n", val);
}

// Delete element from front
int deleteFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from front\n");
        return -1;
    }
    int val = dq->arr[dq->front];
    if (dq->front == dq->rear) {
        // Last element
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == MAX - 1) {
        dq->front = 0; // wrap around
    } else {
        dq->front++;
    }
    return val;
}

// Delete element from rear
int deleteRear(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from rear\n");
        return -1;
    }
    int val = dq->arr[dq->rear];
    if (dq->front == dq->rear) {
        // Last element
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = MAX - 1; // wrap around
    } else {
        dq->rear--;
    }
    return val;
}

int getFront(Deque* dq) {
    if (isEmpty(dq)) return -1;
    return dq->arr[dq->front];
}

int getRear(Deque* dq) {
    if (isEmpty(dq)) return -1;
    return dq->arr[dq->rear];
}

void display(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (true) {
        printf("%d ", dq->arr[i]);
        if (i == dq->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Deque dq;
    init(&dq);

    printf("--- Testing Double-Ended Queue (Deque) using Circular Array ---\n\n");
    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertFront(&dq, 1);
    insertRear(&dq, 30);

    display(&dq);

    // Overflow check
    insertRear(&dq, 40);

    printf("Front: %d, Rear: %d\n", getFront(&dq), getRear(&dq));

    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from rear : %d\n", deleteRear(&dq));

    display(&dq);

    return 0;
}
