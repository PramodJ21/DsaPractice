#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert a node at the beginning of the list - O(1)
void insertAtBeginning(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->data = val;
    newNode->next = *head;
    *head = newNode;
}

// Insert a node at the end of the list - O(N)
void insertAtEnd(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->data = val;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
}

// Delete a node from the beginning - O(1)
int deleteFromBeginning(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return -1;
    }
    struct Node* temp = *head;
    int val = temp->data;
    *head = (*head)->next;
    free(temp);
    return val;
}

// Delete a node from the end - O(N)
int deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return -1;
    }
    if ((*head)->next == NULL) {
        int val = (*head)->data;
        free(*head);
        *head = NULL;
        return val;
    }

    struct Node* curr = *head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    struct Node* toDelete = curr->next;
    int val = toDelete->data;
    curr->next = NULL;
    free(toDelete);
    return val;
}

// Display the elements of the list
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* curr = head;
    printf("List: ");
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    printf("--- Testing Singly Linked List Operations ---\n\n");
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);
    display(head);

    printf("Deleted from beginning: %d\n", deleteFromBeginning(&head));
    display(head);

    printf("Deleted from end: %d\n", deleteFromEnd(&head));
    display(head);

    printf("Deleted from end: %d\n", deleteFromEnd(&head));
    display(head);

    printf("Deleted from beginning: %d\n", deleteFromBeginning(&head));
    display(head);

    // Underflow check
    deleteFromBeginning(&head);

    return 0;
}
