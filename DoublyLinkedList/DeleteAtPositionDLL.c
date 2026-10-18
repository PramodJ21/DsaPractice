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

// Delete node at 1-based position in doubly linked list
int deleteAtPosition(struct Node** head, int pos) {
    if (*head == NULL) {
        printf("Error: List is empty, cannot delete at position %d\n", pos);
        return -1;
    }
    if (pos < 1) {
        printf("Error: Invalid position %d\n", pos);
        return -1;
    }

    struct Node* curr = *head;

    // Case 1: Delete head node (pos 1)
    if (pos == 1) {
        int val = curr->data;
        *head = curr->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(curr);
        printf("Deleted %d from position 1\n", val);
        return val;
    }

    // Traverse to pos-th node
    for (int i = 1; i < pos && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Error: Position %d is out of bounds\n", pos);
        return -1;
    }

    int val = curr->data;

    // Update neighboring nodes
    curr->prev->next = curr->next;
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }

    free(curr);
    printf("Deleted %d from position %d\n", val, pos);
    return val;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("DLL: ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);

    printf("Original DLL:\n");
    display(head);

    // Delete at middle position (30)
    deleteAtPosition(&head, 3);
    display(head);

    // Delete at beginning (10)
    deleteAtPosition(&head, 1);
    display(head);

    // Delete at end (50)
    deleteAtPosition(&head, 3);
    display(head);

    // Invalid position
    deleteAtPosition(&head, 99);

    return 0;
}
