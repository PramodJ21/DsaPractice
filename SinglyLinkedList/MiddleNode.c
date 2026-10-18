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

// Find middle node using slow and fast pointer (Tortoise and Hare)
struct Node* findMiddle(struct Node* head) {
    if (head == NULL) return NULL;

    struct Node* slow = head;
    struct Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // Move by 1 step
        fast = fast->next->next;    // Move by 2 steps
    }

    return slow;
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    // Odd length test
    struct Node* list1 = NULL;
    for (int i = 1; i <= 5; i++) insertAtEnd(&list1, i * 10);
    printf("Odd Length List (5 nodes):\n");
    display(list1);
    struct Node* mid1 = findMiddle(list1);
    if (mid1) printf("Middle Node Data: %d\n\n", mid1->data);

    // Even length test
    struct Node* list2 = NULL;
    for (int i = 1; i <= 6; i++) insertAtEnd(&list2, i * 10);
    printf("Even Length List (6 nodes):\n");
    display(list2);
    struct Node* mid2 = findMiddle(list2);
    if (mid2) printf("Middle Node Data (second of middle two): %d\n\n", mid2->data);

    return 0;
}
