#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool isEmpty(Stack* s) {
    return s->top == -1;
}

void displayStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack: [Empty]\n");
        return;
    }
    printf("Stack (bottom to top): [ ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->items[i]);
    }
    printf("] <- TOP is %d\n", s->items[s->top]);
}

void push(Stack* s, int val) {
    if (s->top == MAX - 1) {
        printf("Push(%d) -> OVERFLOW ERROR!\n", val);
        return;
    }
    s->items[++(s->top)] = val;
    printf("Push(%2d) -> ", val);
    displayStack(s);
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Pop()     -> UNDERFLOW ERROR! Stack is already empty.\n");
        return -1;
    }
    int popped = s->items[(s->top)--];
    printf("Pop()     -> Removed %2d | ", popped);
    displayStack(s);
    return popped;
}

typedef enum { OP_PUSH, OP_POP } StackOpType;

typedef struct {
    StackOpType type;
    int val;
} StackOp;

void traceOperations(StackOp ops[], int n) {
    Stack s;
    initStack(&s);

    printf("Executing Stack Operations with Step-by-Step State Tracing:\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        printf("Step %2d | ", i + 1);
        if (ops[i].type == OP_PUSH) {
            push(&s, ops[i].val);
        } else {
            pop(&s);
        }
    }
    printf("============================================================\n");
    printf("Final Stack State: ");
    displayStack(&s);
}

int main() {
    StackOp script[] = {
        {OP_PUSH, 15},
        {OP_PUSH, 30},
        {OP_PUSH, 45},
        {OP_POP,  0},
        {OP_PUSH, 60},
        {OP_POP,  0},
        {OP_POP,  0},
        {OP_POP,  0},
        {OP_POP,  0}, // Triggers underflow
        {OP_PUSH, 90},
        {OP_POP,  0},
        {OP_POP,  0}  // Triggers underflow
    };
    int n = sizeof(script) / sizeof(script[0]);

    traceOperations(script, n);

    return 0;
}
