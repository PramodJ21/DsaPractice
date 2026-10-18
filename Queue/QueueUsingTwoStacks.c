#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int val) {
    if (s->top < MAX - 1) {
        s->arr[++(s->top)] = val;
    }
}

int pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1;
}

int peek(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->arr[s->top];
    }
    return -1;
}

typedef struct {
    Stack s1; // For enqueue
    Stack s2; // For dequeue
} QueueTwoStacks;

void initQueue(QueueTwoStacks* q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

bool isQueueEmpty(QueueTwoStacks* q) {
    return isStackEmpty(&q->s1) && isStackEmpty(&q->s2);
}

// Enqueue element into the queue - O(1)
void enqueue(QueueTwoStacks* q, int val) {
    push(&q->s1, val);
    printf("Enqueued: %d\n", val);
}

// Dequeue element from the queue - Amortized O(1)
int dequeue(QueueTwoStacks* q) {
    if (isQueueEmpty(q)) {
        printf("Queue Underflow! Queue is empty\n");
        return -1;
    }

    // If s2 is empty, transfer all elements from s1 to s2
    if (isStackEmpty(&q->s2)) {
        while (!isStackEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }

    return pop(&q->s2);
}

// Get front element
int getFront(QueueTwoStacks* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    if (isStackEmpty(&q->s2)) {
        while (!isStackEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }
    return peek(&q->s2);
}

int main() {
    QueueTwoStacks q;
    initQueue(&q);

    printf("--- Testing Queue using Two Stacks ---\n\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Front: %d\n", getFront(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    enqueue(&q, 40);
    enqueue(&q, 50);

    printf("Front: %d\n", getFront(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    // Underflow test
    dequeue(&q);

    return 0;
}
