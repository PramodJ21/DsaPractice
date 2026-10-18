#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Push an element onto the stack (at top/head) - O(1)
void push(struct Node** top, int ele) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Stack Overflow (Out of memory)\n");
        return;
    }
    newNode->data = ele;
    newNode->next = *top;
    *top = newNode;
}

// Pop an element from the stack (from top/head) - O(1)
int pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }
    struct Node* temp = *top;
    int poppedVal = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedVal;
}

// Peek at the top element - O(1)
int peek(struct Node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}

int isEmpty(struct Node* top) {
    return top == NULL;
}

// Display all elements from top to bottom
void display(struct Node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top to bottom): ");
    struct Node* curr = top;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    struct Node* stack = NULL;

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    display(stack);

    printf("Top element: %d\n", peek(stack));
    printf("Popped element: %d\n", pop(&stack));
    display(stack);

    return 0;
}

