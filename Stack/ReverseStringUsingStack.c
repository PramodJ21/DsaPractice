#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char items[MAX];
    int top;
} CharStack;

void init(CharStack* s) {
    s->top = -1;
}

int isEmpty(CharStack* s) {
    return s->top == -1;
}

int isFull(CharStack* s) {
    return s->top == MAX - 1;
}

void push(CharStack* s, char ch) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = ch;
}

char pop(CharStack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

// Function to reverse a string in-place using a stack
void reverseString(char* str) {
    int len = strlen(str);
    CharStack s;
    init(&s);

    // Push all characters to stack
    for (int i = 0; i < len; i++) {
        push(&s, str[i]);
    }

    // Pop characters back to overwrite the string
    for (int i = 0; i < len; i++) {
        str[i] = pop(&s);
    }
}

int main() {
    char str1[] = "Hello, World!";
    char str2[] = "Data Structures and Algorithms";

    printf("Original 1: %s\n", str1);
    reverseString(str1);
    printf("Reversed 1: %s\n\n", str1);

    printf("Original 2: %s\n", str2);
    reverseString(str2);
    printf("Reversed 2: %s\n", str2);

    return 0;
}
