#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Insert at beginning - O(1)
void insertAtBeginning(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = *head;

    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
    printf("Inserted %d at beginning\n", val);
}

// Insert at end - O(N)
void insertAtEnd(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        printf("Inserted %d at end (as head)\n", val);
        return;
    }

    struct Node* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->prev = curr;
    printf("Inserted %d at end\n", val);
}

// Delete from beginning - O(1)
int deleteFromBeginning(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return -1;
    }

    struct Node* temp = *head;
    int val = temp->data;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
    printf("Deleted %d from beginning\n", val);
    return val;
}

// Delete from end - O(N)
int deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return -1;
    }

    struct Node* curr = *head;
    if (curr->next == NULL) {
        int val = curr->data;
        free(curr);
        *head = NULL;
        printf("Deleted %d from end (list is now empty)\n", val);
        return val;
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }
    int val = curr->data;
    curr->prev->next = NULL;
    free(curr);
    printf("Deleted %d from end\n", val);
    return val;
}

void displayForward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List (forward): ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    printf("--- Doubly Linked List Basic Operations ---\n\n");
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);

    displayForward(head);

    deleteFromBeginning(&head);
    displayForward(head);

    deleteFromEnd(&head);
    displayForward(head);

    deleteFromBeginning(&head);
    deleteFromBeginning(&head);
    displayForward(head);

    return 0;
}
