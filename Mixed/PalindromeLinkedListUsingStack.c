#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 500

struct Node {
    int data;
    struct Node* next;
};

void insertAtEnd(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* curr = *head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = newNode;
}

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int val) {
    s->items[++(s->top)] = val;
}

int pop(Stack* s) {
    return s->items[(s->top)--];
}

// Determine if linked list is palindrome using a stack
bool isPalindromeUsingStack(struct Node* head) {
    if (head == NULL || head->next == NULL) return true;

    Stack s;
    initStack(&s);

    // Pass 1: Push all elements of the linked list onto the stack
    struct Node* curr = head;
    while (curr != NULL) {
        push(&s, curr->data);
        curr = curr->next;
    }

    // Pass 2: Traverse list again and compare with popped values
    curr = head;
    while (curr != NULL) {
        int poppedVal = pop(&s);
        if (curr->data != poppedVal) {
            return false; // Mismatch
        }
        curr = curr->next;
    }

    return true;
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    // List 1: Palindrome (1 -> 2 -> 3 -> 2 -> 1)
    struct Node* l1 = NULL;
    int a1[] = {1, 2, 3, 2, 1};
    for (int i = 0; i < 5; i++) insertAtEnd(&l1, a1[i]);
    printf("List 1: ");
    display(l1);
    printf("Is Palindrome? %s\n\n", isPalindromeUsingStack(l1) ? "YES" : "NO");

    // List 2: Even Palindrome (1 -> 2 -> 2 -> 1)
    struct Node* l2 = NULL;
    int a2[] = {1, 2, 2, 1};
    for (int i = 0; i < 4; i++) insertAtEnd(&l2, a2[i]);
    printf("List 2: ");
    display(l2);
    printf("Is Palindrome? %s\n\n", isPalindromeUsingStack(l2) ? "YES" : "NO");

    // List 3: Not Palindrome (1 -> 2 -> 3 -> 4)
    struct Node* l3 = NULL;
    int a3[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) insertAtEnd(&l3, a3[i]);
    printf("List 3: ");
    display(l3);
    printf("Is Palindrome? %s\n", isPalindromeUsingStack(l3) ? "YES" : "NO");

    return 0;
}
