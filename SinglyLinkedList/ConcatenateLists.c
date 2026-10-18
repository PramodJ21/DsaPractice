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

// Concatenate list2 to the end of list1 without creating new nodes
struct Node* concatenate(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Node* curr = head1;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = head2;
    return head1;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    insertAtEnd(&list1, 10);
    insertAtEnd(&list1, 20);
    insertAtEnd(&list1, 30);

    insertAtEnd(&list2, 40);
    insertAtEnd(&list2, 50);
    insertAtEnd(&list2, 60);

    printf("List 1: ");
    display(list1);

    printf("List 2: ");
    display(list2);

    struct Node* combined = concatenate(list1, list2);

    printf("\nConcatenated List (by pointer adjustment): ");
    display(combined);

    return 0;
}
