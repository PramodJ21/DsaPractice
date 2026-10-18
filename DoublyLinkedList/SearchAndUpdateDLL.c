#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Search for a value and return 1-based position (-1 if not found)
int search(struct Node* head, int target) {
    int pos = 1;
    struct Node* curr = head;

    while (curr != NULL) {
        if (curr->data == target) {
            return pos;
        }
        curr = curr->next;
        pos++;
    }
    return -1;
}

// Update the value of the node at 1-based position
bool updateAtPosition(struct Node* head, int pos, int newVal) {
    if (pos < 1 || head == NULL) {
        printf("Error: Invalid position or empty list\n");
        return false;
    }

    struct Node* curr = head;
    for (int i = 1; i < pos && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Error: Position %d is out of bounds!\n", pos);
        return false;
    }

    int oldVal = curr->data;
    curr->data = newVal;
    printf("Updated position %d: changed %d -> %d\n", pos, oldVal, newVal);
    return true;
}

void display(struct Node* head) {
    printf("DLL: ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);

    printf("Original DLL:\n");
    display(head);

    // Search tests
    int targets[] = {300, 100, 999};
    for (int i = 0; i < 3; i++) {
        int pos = search(head, targets[i]);
        if (pos != -1) {
            printf("Target %d found at position %d\n", targets[i], pos);
        } else {
            printf("Target %d not found in list\n", targets[i]);
        }
    }

    // Update tests
    printf("\n--- Updating Node Values ---\n");
    updateAtPosition(head, 3, 350); // Valid position
    updateAtPosition(head, 1, 150); // Head update
    updateAtPosition(head, 10, 999); // Out of bounds
    display(head);

    return 0;
}
