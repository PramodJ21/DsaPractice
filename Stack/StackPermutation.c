#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000

typedef struct {
    int items[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

bool isEmpty(Stack* s) {
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

// Function to check if target array is a valid stack permutation of input array
bool isStackPermutation(const int inArr[], const int outArr[], int n) {
    Stack s;
    init(&s);

    int j = 0; // Pointer for outArr

    for (int i = 0; i < n; i++) {
        // Push incoming element onto the stack
        push(&s, inArr[i]);

        // Pop elements while top of stack matches next required output element
        while (!isEmpty(&s) && peek(&s) == outArr[j]) {
            pop(&s);
            j++;
        }
    }

    // If stack is completely empty, all elements matched the desired output
    return isEmpty(&s) && (j == n);
}

void testPermutation(const int inArr[], const int outArr[], int n) {
    printf("Input Sequence : [");
    for (int i = 0; i < n; i++) printf("%d%s", inArr[i], (i == n - 1) ? "" : ", ");
    printf("]\n");

    printf("Target Sequence: [");
    for (int i = 0; i < n; i++) printf("%d%s", outArr[i], (i == n - 1) ? "" : ", ");
    printf("]\n");

    if (isStackPermutation(inArr, outArr, n)) {
        printf("Result: YES, this is a valid stack permutation.\n\n");
    } else {
        printf("Result: NO, cannot be produced via stack operations.\n\n");
    }
}

int main() {
    printf("--- Checking Stack Permutations ---\n\n");

    int in1[] = {1, 2, 3};
    int out1[] = {2, 1, 3};
    testPermutation(in1, out1, 3); // Valid

    int in2[] = {1, 2, 3};
    int out2[] = {3, 1, 2};
    testPermutation(in2, out2, 3); // Invalid

    int in3[] = {1, 2, 3, 4};
    int out3[] = {2, 4, 3, 1};
    testPermutation(in3, out3, 4); // Valid

    return 0;
}
