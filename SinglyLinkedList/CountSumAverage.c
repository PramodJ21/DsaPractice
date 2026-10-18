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

void computeStats(struct Node* head, int* count, long* sum, double* avg) {
    *count = 0;
    *sum = 0;
    *avg = 0.0;

    if (head == NULL) return;

    struct Node* curr = head;
    while (curr != NULL) {
        (*count)++;
        *sum += curr->data;
        curr = curr->next;
    }

    if (*count > 0) {
        *avg = (double)(*sum) / (*count);
    }
}

void display(struct Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int values[] = {12, 24, 36, 48, 60, 72};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insertAtEnd(&head, values[i]);
    }

    display(head);

    int count = 0;
    long sum = 0;
    double avg = 0.0;

    computeStats(head, &count, &sum, &avg);

    printf("Total Nodes : %d\n", count);
    printf("Sum of Data : %ld\n", sum);
    printf("Average Data: %.2f\n", avg);

    return 0;
}
