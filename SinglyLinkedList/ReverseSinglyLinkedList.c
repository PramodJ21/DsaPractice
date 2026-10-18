#include <stdio.h>
#include <stdlib.h>

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

// In-place pointer reversal of singly linked list (O(N) time, O(1) space)
void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* curr = *head;
    struct Node* nextNode = NULL;

    while (curr != NULL) {
        nextNode = curr->next; // Store next node
        curr->next = prev;     // Reverse current node's pointer
        prev = curr;           // Advance prev
        curr = nextNode;       // Advance curr
    }

    *head = prev; // Update head to new first node
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    for (int i = 1; i <= 6; i++) {
        insertAtEnd(&head, i * 10);
    }

    printf("Original List:\n");
    display(head);

    reverseList(&head);

    printf("\nReversed List (In-place link modification):\n");
    display(head);

    return 0;
}
