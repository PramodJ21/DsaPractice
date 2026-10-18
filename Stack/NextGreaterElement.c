#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int items[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int val) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = val;
    }
}

int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

int peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return -1;
}

// Function to find Next Greater Element for each element in O(N) using a stack
void findNextGreaterElements(int arr[], int n, int nge[]) {
    Stack s;
    init(&s);

    // Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements smaller than or equal to current element
        while (!isEmpty(&s) && peek(&s) <= arr[i]) {
            pop(&s);
        }

        // If stack is empty, no greater element exists to the right
        if (isEmpty(&s)) {
            nge[i] = -1;
        } else {
            nge[i] = peek(&s);
        }

        // Push current element for subsequent elements on left
        push(&s, arr[i]);
    }
}

void printResult(int arr[], int nge[], int n) {
    printf("%-10s %-20s\n", "Element", "Next Greater Element");
    printf("------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20d\n", arr[i], nge[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {4, 5, 2, 25};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int nge1[n1];
    findNextGreaterElements(arr1, n1, nge1);
    printf("Array 1: [4, 5, 2, 25]\n");
    printResult(arr1, nge1, n1);

    int arr2[] = {13, 7, 6, 12};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int nge2[n2];
    findNextGreaterElements(arr2, n2, nge2);
    printf("Array 2: [13, 7, 6, 12]\n");
    printResult(arr2, nge2, n2);

    return 0;
}
