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

// Find k-th node from the end in a single traversal
struct Node* findKthFromEnd(struct Node* head, int k) {
    if (head == NULL || k <= 0) return NULL;

    struct Node* ref_ptr = head;
    struct Node* main_ptr = head;

    // Advance ref_ptr by k nodes
    for (int i = 0; i < k; i++) {
        if (ref_ptr == NULL) {
            printf("Error: k=%d is greater than the total number of nodes in the list.\n", k);
            return NULL;
        }
        ref_ptr = ref_ptr->next;
    }

    // Move both pointers until ref_ptr reaches the end
    while (ref_ptr != NULL) {
        main_ptr = main_ptr->next;
        ref_ptr = ref_ptr->next;
    }

    return main_ptr;
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) insertAtEnd(&head, arr[i]);

    printf("Linked List:\n");
    display(head);

    int testK[] = {1, 3, 7, 10};
    for (int i = 0; i < 4; i++) {
        int k = testK[i];
        struct Node* res = findKthFromEnd(head, k);
        if (res != NULL) {
            printf("%d-th node from the end is: %d\n", k, res->data);
        }
    }

    return 0;
}
