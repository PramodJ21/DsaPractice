#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char items[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

bool isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char ch) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = ch;
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

// Function to check if parentheses, brackets, and braces are balanced
bool isBalanced(const char* expr) {
    Stack s;
    init(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // If opening bracket, push onto stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        // If closing bracket, check for matching top
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) {
                return false; // Closing bracket without opening bracket
            }
            char topChar = pop(&s);
            if (!isMatchingPair(topChar, ch)) {
                return false; // Mismatched bracket types
            }
        }
    }

    // Stack should be empty if all opening brackets were matched
    return isEmpty(&s);
}

int main() {
    const char* tests[] = {
        "{(a+b)*[c-d]}",
        "{(a+b]}",
        "[()]{}{[()()]()}",
        "[(])",
        "((a + b) * (c - d))",
        "((a + b)"
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("--- Checking Balanced Parentheses ---\n");
    for (int i = 0; i < n; i++) {
        printf("Expression: %-20s -> %s\n", tests[i], 
               isBalanced(tests[i]) ? "Balanced" : "Not Balanced");
    }

    return 0;
}
