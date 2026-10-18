#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

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
    printf("Error: Stack underflow in evaluation!\n");
    return 0;
}

int evaluatePostfix(const char* expr) {
    Stack s;
    init(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // If operand (single digit), push onto stack
        if (isdigit(ch)) {
            push(&s, ch - '0');
        }
        // If operator, pop two operands and compute
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            int val2 = pop(&s);
            int val1 = pop(&s);
            int result = 0;

            switch (ch) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        return 0;
                    }
                    result = val1 / val2; 
                    break;
                case '^': result = (int)pow(val1, val2); break;
            }
            push(&s, result);
        }
    }

    return pop(&s);
}

int main() {
    const char* expr1 = "23*54*+";
    const char* expr2 = "231*+9-";
    const char* expr3 = "62/3-42*+";

    printf("Postfix Expression: %s => Evaluated Result: %d\n", expr1, evaluatePostfix(expr1));
    printf("Postfix Expression: %s => Evaluated Result: %d\n", expr2, evaluatePostfix(expr2));
    printf("Postfix Expression: %s => Evaluated Result: %d\n", expr3, evaluatePostfix(expr3));

    return 0;
}
