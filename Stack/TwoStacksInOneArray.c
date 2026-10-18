#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int arr[MAX];
    int top1;
    int top2;
} TwoStacks;

void init(TwoStacks* ts) {
    ts->top1 = -1;
    ts->top2 = MAX;
}

// Push to Stack 1 (grows from left to right)
void push1(TwoStacks* ts, int val) {
    if (ts->top1 + 1 == ts->top2) {
        printf("Stack Overflow! Cannot push %d to Stack 1 (no space left in array)\n", val);
        return;
    }
    ts->arr[++(ts->top1)] = val;
    printf("Pushed %d to Stack 1\n", val);
}

// Push to Stack 2 (grows from right to left)
void push2(TwoStacks* ts, int val) {
    if (ts->top1 + 1 == ts->top2) {
        printf("Stack Overflow! Cannot push %d to Stack 2 (no space left in array)\n", val);
        return;
    }
    ts->arr[--(ts->top2)] = val;
    printf("Pushed %d to Stack 2\n", val);
}

// Pop from Stack 1
int pop1(TwoStacks* ts) {
    if (ts->top1 == -1) {
        printf("Stack Underflow! Stack 1 is empty\n");
        return -1;
    }
    return ts->arr[(ts->top1)--];
}

// Pop from Stack 2
int pop2(TwoStacks* ts) {
    if (ts->top2 == MAX) {
        printf("Stack Underflow! Stack 2 is empty\n");
        return -1;
    }
    return ts->arr[(ts->top2)++];
}

// Display Stack 1
void display1(TwoStacks* ts) {
    if (ts->top1 == -1) {
        printf("Stack 1 is empty\n");
        return;
    }
    printf("Stack 1 (top to bottom): ");
    for (int i = ts->top1; i >= 0; i--) {
        printf("%d ", ts->arr[i]);
    }
    printf("\n");
}

// Display Stack 2
void display2(TwoStacks* ts) {
    if (ts->top2 == MAX) {
        printf("Stack 2 is empty\n");
        return;
    }
    printf("Stack 2 (top to bottom): ");
    for (int i = ts->top2; i < MAX; i++) {
        printf("%d ", ts->arr[i]);
    }
    printf("\n");
}

int main() {
    TwoStacks ts;
    init(&ts);

    printf("--- Two Stacks in a Single Array (Capacity: %d) ---\n\n", MAX);

    // Push into Stack 1
    push1(&ts, 5);
    push1(&ts, 10);
    push1(&ts, 15);

    // Push into Stack 2
    push2(&ts, 100);
    push2(&ts, 200);
    push2(&ts, 300);

    display1(&ts);
    display2(&ts);

    // Fill remaining elements to trigger overflow
    push1(&ts, 20);
    push2(&ts, 400);
    push1(&ts, 25);
    push2(&ts, 500);

    // This should trigger overflow
    push1(&ts, 30);
    push2(&ts, 600);

    printf("\nPopping from Stack 1: %d\n", pop1(&ts));
    printf("Popping from Stack 2: %d\n", pop2(&ts));

    display1(&ts);
    display2(&ts);

    return 0;
}
