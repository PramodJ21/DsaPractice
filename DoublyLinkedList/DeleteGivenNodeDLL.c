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

// Delete a given node directly in O(1) without searching
void deleteGivenNode(struct Node** head, struct Node* del) {
    if (*head == NULL || del == NULL) {
        return;
    }

    // Case 1: Node to be deleted is the head node
    if (*head == del) {
        *head = del->next;
    }

    // Case 2: Node is not the last node
    if (del->next != NULL) {
        del->next->prev = del->prev;
    }

    // Case 3: Node is not the first node
    if (del->prev != NULL) {
        del->prev->next = del->next;
    }

    printf("Deleted node with data: %d in O(1) time\n", del->data);
    free(del);
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
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
    for (int i = 1; i <= 5; i++) insertAtEnd(&head, i * 10);

    printf("Original DLL: ");
    display(head);

    // Get pointer to 3rd node (30)
    struct Node* node30 = head->next->next;
    deleteGivenNode(&head, node30);
    display(head);

    // Delete head node directly (10)
    deleteGivenNode(&head, head);
    display(head);

    // Delete tail node (50)
    struct Node* tail = head;
    while (tail->next != NULL) tail = tail->next;
    deleteGivenNode(&head, tail);
    display(head);

    return 0;
}
