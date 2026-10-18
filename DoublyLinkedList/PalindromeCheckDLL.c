#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

void insertAtEnd(struct Node** head, struct Node** tail, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = *tail;

    if (*tail != NULL) {
        (*tail)->next = newNode;
    } else {
        *head = newNode;
    }
    *tail = newNode;
}

// Check if DLL is a palindrome by comparing nodes from both ends inward
bool isPalindrome(struct Node* head, struct Node* tail) {
    if (head == NULL || head == tail) return true;

    struct Node* left = head;
    struct Node* right = tail;

    // Continue until pointers meet (odd length) or cross each other (even length)
    while (left != right && left->prev != right) {
        if (left->data != right->data) {
            return false;
        }
        left = left->next;
        right = right->prev;
    }
    return true;
}

void display(struct Node* head) {
    printf("DLL: ");
    while (head != NULL) {
        printf("%d ", head->data);
        if (head->next != NULL) printf("<-> ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Test 1: Palindrome (odd length) 1 <-> 2 <-> 3 <-> 2 <-> 1
    struct Node* h1 = NULL;
    struct Node* t1 = NULL;
    int a1[] = {1, 2, 3, 2, 1};
    for (int i = 0; i < 5; i++) insertAtEnd(&h1, &t1, a1[i]);
    display(h1);
    printf("Result 1: %s\n\n", isPalindrome(h1, t1) ? "Palindrome" : "Not Palindrome");

    // Test 2: Palindrome (even length) 10 <-> 20 <-> 20 <-> 10
    struct Node* h2 = NULL;
    struct Node* t2 = NULL;
    int a2[] = {10, 20, 20, 10};
    for (int i = 0; i < 4; i++) insertAtEnd(&h2, &t2, a2[i]);
    display(h2);
    printf("Result 2: %s\n\n", isPalindrome(h2, t2) ? "Palindrome" : "Not Palindrome");

    // Test 3: Not palindrome
    struct Node* h3 = NULL;
    struct Node* t3 = NULL;
    int a3[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) insertAtEnd(&h3, &t3, a3[i]);
    display(h3);
    printf("Result 3: %s\n", isPalindrome(h3, t3) ? "Palindrome" : "Not Palindrome");

    return 0;
}
