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

// Remove every occurrence of target value, including at head and tail
int deleteAllOccurrences(struct Node** head, int target) {
    int deleteCount = 0;

    // Handle leading nodes with target value
    while (*head != NULL && (*head)->data == target) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        deleteCount++;
    }

    if (*head == NULL) {
        return deleteCount;
    }

    // Handle non-head nodes
    struct Node* curr = *head;
    while (curr->next != NULL) {
        if (curr->next->data == target) {
            struct Node* toDelete = curr->next;
            curr->next = toDelete->next;
            free(toDelete);
            deleteCount++;
        } else {
            curr = curr->next;
        }
    }

    return deleteCount;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty (NULL)\n");
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
    // List with target '20' at start, middle, and end: 20 -> 20 -> 10 -> 20 -> 30 -> 20
    int values[] = {20, 20, 10, 20, 30, 20};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) insertAtEnd(&head, values[i]);

    printf("Original List (Contains multiple 20s at beginning, middle, and end):\n");
    display(head);

    int count = deleteAllOccurrences(&head, 20);
    printf("\nDeleted %d occurrence(s) of value 20.\n", count);

    printf("Updated List:\n");
    display(head);

    return 0;
}
