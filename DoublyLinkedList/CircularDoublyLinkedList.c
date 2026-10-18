#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Check if list is empty
bool isEmpty(struct Node* head) {
    return head == NULL;
}

// Check if a node is the last node (tail)
bool isLastNode(struct Node* head, struct Node* node) {
    if (head == NULL || node == NULL) return false;
    return (node->next == head);
}

// Find first node containing value x
struct Node* find(struct Node* head, int x) {
    if (isEmpty(head)) return NULL;
    struct Node* curr = head;
    do {
        if (curr->data == x) return curr;
        curr = curr->next;
    } while (curr != head);
    return NULL;
}

// Find predecessor of first node containing value x
struct Node* findPrev(struct Node* head, int x) {
    struct Node* target = find(head, x);
    return (target != NULL) ? target->prev : NULL;
}

// Find successor of first node containing value x
struct Node* findNext(struct Node* head, int x) {
    struct Node* target = find(head, x);
    return (target != NULL) ? target->next : NULL;
}

// Insert at head
void insertAtHead(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;

    if (*head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
        return;
    }

    struct Node* tail = (*head)->prev;
    newNode->next = *head;
    newNode->prev = tail;
    tail->next = newNode;
    (*head)->prev = newNode;
    *head = newNode;
}

// Insert at tail
void insertAtTail(struct Node** head, int val) {
    if (*head == NULL) {
        insertAtHead(head, val);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;

    struct Node* tail = (*head)->prev;
    newNode->next = *head;
    newNode->prev = tail;
    tail->next = newNode;
    (*head)->prev = newNode;
}

// Insert at 1-based position
void insertAtPosition(struct Node** head, int val, int pos) {
    if (pos < 1) {
        printf("Invalid position %d\n", pos);
        return;
    }
    if (pos == 1 || *head == NULL) {
        insertAtHead(head, val);
        return;
    }

    struct Node* curr = *head;
    for (int i = 1; i < pos - 1; i++) {
        curr = curr->next;
        if (curr == *head) {
            printf("Position %d out of bounds! Appending to tail.\n", pos);
            insertAtTail(head, val);
            return;
        }
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = curr->next;
    newNode->prev = curr;
    curr->next->prev = newNode;
    curr->next = newNode;
}

// Delete from head
int deleteFromHead(struct Node** head) {
    if (isEmpty(*head)) {
        printf("List is empty! Nothing to delete.\n");
        return -1;
    }

    int val = (*head)->data;
    if ((*head)->next == *head) {
        // Only one node
        free(*head);
        *head = NULL;
        return val;
    }

    struct Node* tail = (*head)->prev;
    struct Node* temp = *head;
    *head = (*head)->next;
    (*head)->prev = tail;
    tail->next = *head;
    free(temp);
    return val;
}

// Delete from tail
int deleteFromTail(struct Node** head) {
    if (isEmpty(*head)) {
        printf("List is empty! Nothing to delete.\n");
        return -1;
    }
    if ((*head)->next == *head) {
        return deleteFromHead(head);
    }

    struct Node* tail = (*head)->prev;
    int val = tail->data;
    struct Node* newTail = tail->prev;
    newTail->next = *head;
    (*head)->prev = newTail;
    free(tail);
    return val;
}

// Delete at 1-based position
int deleteAtPosition(struct Node** head, int pos) {
    if (isEmpty(*head) || pos < 1) {
        printf("Invalid deletion position or empty list\n");
        return -1;
    }
    if (pos == 1) {
        return deleteFromHead(head);
    }

    struct Node* curr = *head;
    for (int i = 1; i < pos; i++) {
        curr = curr->next;
        if (curr == *head) {
            printf("Position %d is out of bounds!\n", pos);
            return -1;
        }
    }

    int val = curr->data;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);
    return val;
}

// Update value at 1-based position
bool update(struct Node* head, int pos, int newVal) {
    if (isEmpty(head) || pos < 1) return false;
    struct Node* curr = head;
    for (int i = 1; i < pos; i++) {
        curr = curr->next;
        if (curr == head) return false;
    }
    curr->data = newVal;
    return true;
}

// Display circular list
void display(struct Node* head) {
    if (isEmpty(head)) {
        printf("Circular DLL: [Empty]\n");
        return;
    }
    printf("Circular DLL: ");
    struct Node* curr = head;
    do {
        printf("%d ", curr->data);
        curr = curr->next;
        printf("<=> ");
    } while (curr != head);
    printf("(head: %d)\n", head->data);
}

// Delete entire list
void deleteEntireList(struct Node** head) {
    if (isEmpty(*head)) return;

    struct Node* curr = *head;
    struct Node* tail = (*head)->prev;
    tail->next = NULL; // Break circular link

    while (curr != NULL) {
        struct Node* nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }
    *head = NULL;
    printf("Entire circular doubly linked list successfully deleted.\n");
}

int main() {
    struct Node* cdll = NULL;

    printf("--- Testing Complete Circular Doubly Linked List ---\n\n");
    insertAtTail(&cdll, 20);
    insertAtTail(&cdll, 30);
    insertAtHead(&cdll, 10);
    insertAtTail(&cdll, 40);
    insertAtPosition(&cdll, 25, 3); // between 20 and 30
    display(cdll);

    // Queries
    struct Node* found = find(cdll, 25);
    if (found) printf("Found 25! Is last node? %s\n", isLastNode(cdll, found) ? "Yes" : "No");

    struct Node* prevNode = findPrev(cdll, 10);
    if (prevNode) printf("Predecessor of 10 (head) wrapped to tail: %d\n", prevNode->data);

    struct Node* nextNode = findNext(cdll, 40);
    if (nextNode) printf("Successor of 40 (tail) wrapped to head: %d\n", nextNode->data);

    // Updates
    update(cdll, 3, 27);
    printf("Updated position 3 to 27: ");
    display(cdll);

    // Deletions
    printf("Deleted from head: %d\n", deleteFromHead(&cdll));
    display(cdll);

    printf("Deleted from tail: %d\n", deleteFromTail(&cdll));
    display(cdll);

    printf("Deleted from position 2: %d\n", deleteAtPosition(&cdll, 2));
    display(cdll);

    deleteEntireList(&cdll);
    display(cdll);

    return 0;
}
