#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Initialize stack
void initStack(Stack* s) {
    s->top = -1;
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// Check if stack is full
bool isFull(Stack* s) {
    return s->top == MAX - 1;
}

// Push an element onto stack
void push(Stack* s, int val) {
    if (isFull(s)) {
        printf("Stack Overflow! Cannot push %d\n", val);
        return;
    }
    s->arr[++(s->top)] = val;
    printf("Pushed %d onto stack\n", val);
}

// Pop an element from stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow! Stack is empty\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// Peek top element without removing
int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->arr[s->top];
}

// Display elements from top to bottom
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initStack(&s);

    printf("--- Testing Stack using Array ---\n");
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);

    // Overflow check
    push(&s, 60);

    display(&s);

    printf("Top element (peek): %d\n", peek(&s));

    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));

    display(&s);
    printf("Is empty? %s\n", isEmpty(&s) ? "Yes" : "No");
    printf("Is full? %s\n", isFull(&s) ? "Yes" : "No");

    return 0;
}
