#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

void insertAtEnd(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* curr = *head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = newNode;
    newNode->prev = curr;
}

// Reverse DLL by swapping prev and next pointers for each node
void reverseDLL(struct Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // Empty or single node
    }

    struct Node* temp = NULL;
    struct Node* curr = *head;

    while (curr != NULL) {
        // Swap prev and next pointers
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        // Move to next node in original order (which is now curr->prev)
        curr = curr->prev;
    }

    // Before the last swap, temp was pointing to the predecessor of the last node
    if (temp != NULL) {
        *head = temp->prev;
    }
}

void display(struct Node* head) {
    printf("DLL: NULL <-> ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {10, 20, 30, 40, 50, 60};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) insertAtEnd(&head, arr[i]);

    printf("Original Doubly Linked List:\n");
    display(head);

    reverseDLL(&head);

    printf("\nReversed Doubly Linked List (swapped prev and next links):\n");
    display(head);

    return 0;
}
