#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert a node at a 1-based position
void insertAtPosition(struct Node** head, int val, int pos) {
    if (pos < 1) {
        printf("Invalid position %d! Position must be >= 1.\n", pos);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = val;

    // Insertion at the head (pos == 1)
    if (pos == 1) {
        newNode->next = *head;
        *head = newNode;
        printf("Inserted %d at position 1\n", val);
        return;
    }

    struct Node* curr = *head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Invalid position %d! Position is out of bounds.\n", pos);
        free(newNode);
        return;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    printf("Inserted %d at position %d\n", val, pos);
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    printf("--- Inserting Nodes at 1-based Positions ---\n\n");
    insertAtPosition(&head, 10, 1); // at pos 1
    insertAtPosition(&head, 30, 2); // at pos 2
    insertAtPosition(&head, 20, 2); // between 10 and 30
    insertAtPosition(&head, 5, 1);  // new head
    insertAtPosition(&head, 40, 5); // at end
    display(head);

    // Invalid position tests
    insertAtPosition(&head, 99, 10); // out of bounds
    insertAtPosition(&head, 88, 0);  // invalid < 1
    display(head);

    return 0;
}
