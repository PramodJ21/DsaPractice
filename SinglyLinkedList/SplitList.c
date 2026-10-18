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

// Split singly linked list into two halves using slow and fast pointers
void splitList(struct Node* source, struct Node** firstHalf, struct Node** secondHalf) {
    if (source == NULL) {
        *firstHalf = NULL;
        *secondHalf = NULL;
        return;
    }
    if (source->next == NULL) {
        *firstHalf = source;
        *secondHalf = NULL;
        return;
    }

    struct Node* slow = source;
    struct Node* fast = source->next;

    // Advance fast by 2 and slow by 1
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // slow is at midpoint: split after slow
    *firstHalf = source;
    *secondHalf = slow->next;
    slow->next = NULL; // Break link
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
    // Test with even number of nodes
    struct Node* listEven = NULL;
    for (int i = 1; i <= 6; i++) insertAtEnd(&listEven, i * 10);

    printf("Original Even List (6 nodes): ");
    display(listEven);

    struct Node* half1 = NULL;
    struct Node* half2 = NULL;
    splitList(listEven, &half1, &half2);

    printf("First Half : ");
    display(half1);
    printf("Second Half: ");
    display(half2);

    // Test with odd number of nodes
    struct Node* listOdd = NULL;
    for (int i = 1; i <= 5; i++) insertAtEnd(&listOdd, i);

    printf("\nOriginal Odd List (5 nodes): ");
    display(listOdd);

    struct Node* oddHalf1 = NULL;
    struct Node* oddHalf2 = NULL;
    splitList(listOdd, &oddHalf1, &oddHalf2);

    printf("First Half (ceil): ");
    display(oddHalf1);
    printf("Second Half      : ");
    display(oddHalf2);

    return 0;
}
