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

// Merge two sorted singly linked lists in-place by adjusting pointers
struct Node* mergeSortedLists(struct Node* l1, struct Node* l2) {
    struct Node dummy;
    dummy.next = NULL;
    struct Node* tail = &dummy;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Attach remaining elements
    tail->next = (l1 != NULL) ? l1 : l2;

    return dummy.next;
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* l1 = NULL;
    struct Node* l2 = NULL;

    int arr1[] = {5, 10, 15, 40};
    int arr2[] = {2, 3, 20, 35, 50};

    for (int i = 0; i < 4; i++) insertAtEnd(&l1, arr1[i]);
    for (int i = 0; i < 5; i++) insertAtEnd(&l2, arr2[i]);

    printf("Sorted List 1: ");
    display(l1);

    printf("Sorted List 2: ");
    display(l2);

    struct Node* merged = mergeSortedLists(l1, l2);

    printf("\nMerged Sorted List (In-place pointer adjustment): ");
    display(merged);

    return 0;
}
