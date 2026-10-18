#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct {
    struct Node* head;
    struct Node* tail;
} DoublyList;

void init(DoublyList* list) {
    list->head = NULL;
    list->tail = NULL;
}

void insertEnd(DoublyList* list, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
}

// Delete all nodes and reset head and tail pointers
void clearList(DoublyList* list) {
    struct Node* curr = list->head;
    int freedCount = 0;

    while (curr != NULL) {
        struct Node* nextNode = curr->next;
        free(curr);
        curr = nextNode;
        freedCount++;
    }

    list->head = NULL;
    list->tail = NULL;
    printf("Successfully freed all %d nodes. Head and tail reset to NULL.\n", freedCount);
}

void display(DoublyList* list) {
    if (list->head == NULL) {
        printf("List is empty (head = NULL, tail = NULL)\n");
        return;
    }
    printf("List (head to tail): ");
    struct Node* curr = list->head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->next != NULL) printf("<-> ");
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    DoublyList list;
    init(&list);

    for (int i = 1; i <= 5; i++) {
        insertEnd(&list, i * 10);
    }

    printf("Before clearing:\n");
    display(&list);

    clearList(&list);

    printf("\nAfter clearing:\n");
    display(&list);

    // Re-inserting to verify list can be reused after reset
    printf("\nRe-inserting elements after full reset:\n");
    insertEnd(&list, 100);
    insertEnd(&list, 200);
    display(&list);

    return 0;
}
