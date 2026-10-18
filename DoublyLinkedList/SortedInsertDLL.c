#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Insert into sorted DLL preserving ascending order and all prev/next links
void sortedInsert(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->prev = NULL;
    newNode->next = NULL;

    // Case 1: List is empty
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Case 2: Insert before current head
    if (val <= (*head)->data) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    // Case 3: Locate insertion position in list
    struct Node* curr = *head;
    while (curr->next != NULL && curr->next->data < val) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = newNode;
    }
    curr->next = newNode;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->next != NULL) printf("<-> ");
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    printf("--- Sorted Insert into Doubly Linked List ---\n\n");
    int elements[] = {30, 10, 50, 20, 5, 40, 25};
    int n = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < n; i++) {
        printf("Inserting %2d -> ", elements[i]);
        sortedInsert(&head, elements[i]);
        display(head);
    }

    return 0;
}
