#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Detailed visual display showing node data, memory addresses, and next pointers
void traceList(struct Node* head) {
    if (head == NULL) {
        printf("  List Pointer State: head -> NULL (List is empty)\n");
        return;
    }

    printf("  List Pointer State:\n");
    printf("    head pointer points to: %p\n", (void*)head);
    struct Node* curr = head;
    int index = 1;
    while (curr != NULL) {
        printf("    Node #%d [%p]: data = %2d | next -> %p\n", 
               index++, (void*)curr, curr->data, (void*)curr->next);
        curr = curr->next;
    }
    printf("    Summary list chain: ");
    curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

// Insert at tail with pointer trace
void insertTail(struct Node** head, int val) {
    printf("\n>>> ACTION: Insert %d at TAIL\n", val);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    printf("  Allocated new node at %p with data = %d, next = NULL\n", (void*)newNode, val);

    if (*head == NULL) {
        *head = newNode;
        printf("  List was empty: updated head pointer -> %p\n", (void*)newNode);
    } else {
        struct Node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        printf("  Found current tail at %p. Setting tail->next (%p) -> newNode (%p)\n", 
               (void*)curr, (void*)curr->next, (void*)newNode);
        curr->next = newNode;
    }
    traceList(*head);
}

// Delete head with pointer trace
void deleteHead(struct Node** head) {
    printf("\n>>> ACTION: Delete HEAD node\n");
    if (*head == NULL) {
        printf("  List is empty! Nothing to delete.\n");
        return;
    }

    struct Node* oldHead = *head;
    printf("  Old head is at %p (data = %d). Updating head pointer to oldHead->next (%p)\n", 
           (void*)oldHead, oldHead->data, (void*)oldHead->next);
    *head = oldHead->next;
    printf("  Freeing memory of old head at %p\n", (void*)oldHead);
    free(oldHead);
    traceList(*head);
}

// Delete last node with pointer trace
void deleteLastNode(struct Node** head) {
    printf("\n>>> ACTION: Delete LAST node\n");
    if (*head == NULL) {
        printf("  List is empty! Nothing to delete.\n");
        return;
    }

    if ((*head)->next == NULL) {
        printf("  Only single node at %p exists. Freeing and setting head -> NULL\n", (void*)*head);
        free(*head);
        *head = NULL;
        traceList(*head);
        return;
    }

    struct Node* curr = *head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    struct Node* lastNode = curr->next;
    printf("  Penultimate node is at %p. Last node to delete is at %p (data = %d)\n", 
           (void*)curr, (void*)lastNode, lastNode->data);
    printf("  Setting penultimate node next from %p to NULL\n", (void*)curr->next);
    curr->next = NULL;
    free(lastNode);
    traceList(*head);
}

int main() {
    struct Node* head = NULL;

    printf("============================================================\n");
    printf("--- Tracing Pointer Changes Across Linked List Operations ---\n");
    printf("============================================================\n");

    traceList(head);

    insertTail(&head, 10);
    insertTail(&head, 20);
    insertTail(&head, 30);
    insertTail(&head, 40);

    deleteHead(&head);

    insertTail(&head, 50);

    deleteLastNode(&head);

    printf("\n============================================================\n");
    printf("FINAL DETERMINED LINKED LIST:\n");
    traceList(head);
    printf("============================================================\n");

    return 0;
}
