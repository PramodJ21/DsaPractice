#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Insert node at 1-based position in doubly linked list
void insertAtPosition(struct Node** head, int val, int pos) {
    if (pos < 1) {
        printf("Invalid position %d! Must be >= 1.\n", pos);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = NULL;

    // Case 1: Insert at beginning
    if (pos == 1) {
        newNode->next = *head;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
        printf("Inserted %d at position 1\n", val);
        return;
    }

    // Traverse to (pos - 1)-th node
    struct Node* curr = *head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Invalid position %d! Position out of bounds.\n", pos);
        free(newNode);
        return;
    }

    // Insert after curr
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = newNode;
    }
    curr->next = newNode;
    printf("Inserted %d at position %d\n", val, pos);
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

    printf("--- Inserting into DLL at Specific Positions ---\n\n");
    insertAtPosition(&head, 10, 1); // pos 1
    insertAtPosition(&head, 30, 2); // pos 2
    insertAtPosition(&head, 20, 2); // between 10 and 30
    insertAtPosition(&head, 5, 1);  // new head
    insertAtPosition(&head, 40, 5); // at end
    display(head);

    // Invalid position tests
    insertAtPosition(&head, 99, 10);
    insertAtPosition(&head, 88, 0);

    return 0;
}
