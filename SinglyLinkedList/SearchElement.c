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

// Search for value and return 1-based index of first occurrence, or -1 if not found
int search(struct Node* head, int target) {
    int pos = 1;
    struct Node* curr = head;

    while (curr != NULL) {
        if (curr->data == target) {
            return pos; // First occurrence
        }
        curr = curr->next;
        pos++;
    }

    return -1; // Not found
}

void display(struct Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int values[] = {15, 25, 35, 25, 45, 55};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insertAtEnd(&head, values[i]);
    }

    display(head);

    int targets[] = {25, 15, 55, 99};
    for (int i = 0; i < 4; i++) {
        int pos = search(head, targets[i]);
        if (pos != -1) {
            printf("Target %d found at position %d (1-based index)\n", targets[i], pos);
        } else {
            printf("Target %d not found in the list\n", targets[i]);
        }
    }

    return 0;
}
