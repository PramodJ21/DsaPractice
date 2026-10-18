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

// Remove duplicate elements from unsorted list preserving original order
void removeDuplicates(struct Node* head) {
    struct Node* curr = head;

    while (curr != NULL) {
        struct Node* prev = curr;
        struct Node* runner = curr->next;

        while (runner != NULL) {
            if (runner->data == curr->data) {
                // Duplicate found, delete runner node
                prev->next = runner->next;
                free(runner);
                runner = prev->next;
            } else {
                prev = runner;
                runner = runner->next;
            }
        }
        curr = curr->next;
    }
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {12, 11, 12, 21, 41, 43, 21, 11, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) insertAtEnd(&head, arr[i]);

    printf("Original List with Duplicates:\n");
    display(head);

    removeDuplicates(head);

    printf("\nList After Removing Duplicates:\n");
    display(head);

    return 0;
}
