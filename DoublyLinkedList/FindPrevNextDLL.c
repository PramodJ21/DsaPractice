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

// Find node with first occurrence of value x
struct Node* findNode(struct Node* head, int x) {
    struct Node* curr = head;
    while (curr != NULL) {
        if (curr->data == x) return curr;
        curr = curr->next;
    }
    return NULL;
}

// Return pointer to the predecessor of the first node containing value x
struct Node* findPrev(struct Node* head, int x) {
    struct Node* targetNode = findNode(head, x);
    if (targetNode == NULL) {
        printf("Node with value %d does not exist in list.\n", x);
        return NULL;
    }
    return targetNode->prev;
}

// Return pointer to the successor of the first node containing value x
struct Node* findNext(struct Node* head, int x) {
    struct Node* targetNode = findNode(head, x);
    if (targetNode == NULL) {
        printf("Node with value %d does not exist in list.\n", x);
        return NULL;
    }
    return targetNode->next;
}

void display(struct Node* head) {
    printf("DLL: ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);

    printf("Doubly Linked List:\n");
    display(head);

    int testVals[] = {30, 10, 50, 99};
    for (int i = 0; i < 4; i++) {
        int x = testVals[i];
        printf("\nQuery for value x = %d:\n", x);

        struct Node* p = findPrev(head, x);
        if (p != NULL) {
            printf("  Predecessor (prev): %d\n", p->data);
        } else {
            printf("  Predecessor (prev): NULL (none or not found)\n");
        }

        struct Node* n = findNext(head, x);
        if (n != NULL) {
            printf("  Successor   (next): %d\n", n->data);
        } else {
            printf("  Successor   (next): NULL (none or not found)\n");
        }
    }

    return 0;
}
