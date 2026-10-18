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

// Delete node at 1-based position
int deleteAtPosition(struct Node** head, int pos) {
    // Case 1: List is empty
    if (*head == NULL) {
        printf("Error: List is empty, cannot delete at position %d.\n", pos);
        return -1;
    }

    if (pos < 1) {
        printf("Error: Invalid position %d (must be >= 1).\n", pos);
        return -1;
    }

    // Case 2: Deleting the head node (including when it's the only element)
    if (pos == 1) {
        struct Node* temp = *head;
        int val = temp->data;
        *head = (*head)->next;
        free(temp);
        printf("Deleted %d from position 1.\n", val);
        return val;
    }

    // Traverse to (pos - 1)-th node
    struct Node* curr = *head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    // Case 3: Position is out of bounds
    if (curr == NULL || curr->next == NULL) {
        printf("Error: Position %d is out of bounds.\n", pos);
        return -1;
    }

    struct Node* toDelete = curr->next;
    int val = toDelete->data;
    curr->next = toDelete->next;
    free(toDelete);
    printf("Deleted %d from position %d.\n", val, pos);
    return val;
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

    printf("--- Deleting Nodes at Specified Positions ---\n\n");
    // Test on empty list
    deleteAtPosition(&head, 1);

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);
    display(head);

    // Delete at middle position (pos 3 -> 30)
    deleteAtPosition(&head, 3);
    display(head);

    // Delete at beginning (pos 1 -> 10)
    deleteAtPosition(&head, 1);
    display(head);

    // Delete at end (pos 3 -> 50)
    deleteAtPosition(&head, 3);
    display(head);

    // Invalid position (out of bounds)
    deleteAtPosition(&head, 10);

    // Delete remaining until single node remains, then delete single node
    deleteAtPosition(&head, 1);
    display(head);
    deleteAtPosition(&head, 1); // Single node deletion
    display(head);

    return 0;
}
