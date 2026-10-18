#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert a value into a sorted singly linked list preserving ascending order
void sortedInsert(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    // Special case: list is empty or new value is smaller than head's data
    if (*head == NULL || (*head)->data >= val) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Locate the node before the point of insertion
    struct Node* curr = *head;
    while (curr->next != NULL && curr->next->data < val) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
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

    printf("--- Inserting into Sorted Singly Linked List ---\n\n");
    int values[] = {25, 10, 50, 5, 30, 20, 60, 15};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        printf("Inserting %d: ", values[i]);
        sortedInsert(&head, values[i]);
        display(head);
    }

    return 0;
}
