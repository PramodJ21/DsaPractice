#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 200

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

void push(CharStack* s, char ch) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = ch;
    }
}

char pop(CharStack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(CharStack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

// Return precedence of operators
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default:  return -1;
    }
}

// Check associativity: true for right-associative (^), false for left-associative
int isRightAssociative(char op) {
    return (op == '^');
}

// Convert infix expression to postfix
void infixToPostfix(const char* infix, char* postfix) {
    CharStack s;
    init(&s);
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // If operand (letters or digits), directly append to output
        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        // If left parenthesis, push to stack
        else if (ch == '(') {
            push(&s, ch);
        }
        // If right parenthesis, pop until matching '('
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s); // discard '('
            }
        }
        // Operator encountered
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            while (!isEmpty(&s) && peek(&s) != '(' &&
                   (precedence(peek(&s)) > precedence(ch) ||
                    (precedence(peek(&s)) == precedence(ch) && !isRightAssociative(ch)))) {
                postfix[k++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    // Pop all remaining operators
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
}

int main() {
    const char* tests[] = {
        "A+B*C-D",
        "(A+B)*(C-D)",
        "A*(B+C)/D",
        "A+B*(C^D-E)^(F+G*H)-I"
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("--- Infix to Postfix Conversion ---\n");
    for (int i = 0; i < n; i++) {
        char postfix[MAX];
        infixToPostfix(tests[i], postfix);
        printf("Infix  : %s\n", tests[i]);
        printf("Postfix: %s\n\n", postfix);
    }

    return 0;
}
