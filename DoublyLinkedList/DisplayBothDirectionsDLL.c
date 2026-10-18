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

// Display forward (head to tail)
void displayHeadToTail(struct Node* head) {
    printf("Forward (Head to Tail): ");
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

// Display backward (tail to head)
void displayTailToHead(struct Node* head) {
    printf("Backward (Tail to Head): ");
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }
    // Navigate to tail
    struct Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    // Traverse backwards using prev pointers
    while (tail != NULL) {
        printf("%d ", tail->data);
        if (tail->prev != NULL) printf("<-> ");
        tail = tail->prev;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {10, 25, 40, 55, 70, 85};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) insertAtEnd(&head, arr[i]);

    printf("--- Traversing Doubly Linked List in Both Directions ---\n\n");
    displayHeadToTail(head);
    displayTailToHead(head);

    return 0;
}
