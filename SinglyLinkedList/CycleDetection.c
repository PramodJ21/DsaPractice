#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

// Detect cycle and return the node where the cycle begins (Floyd's Cycle Algorithm)
struct Node* detectCycleStart(struct Node* head) {
    if (head == NULL || head->next == NULL) return NULL;

    struct Node* slow = head;
    struct Node* fast = head;

    // Phase 1: Determine if cycle exists
    bool hasCycle = false;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    if (!hasCycle) {
        return NULL; // No cycle
    }

    // Phase 2: Find starting node of the cycle
    struct Node* ptr1 = head;
    struct Node* ptr2 = slow;

    while (ptr1 != ptr2) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return ptr1; // Cycle entry node
}

int main() {
    // Construct linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 3 (cycle starts at 3)
    struct Node* n1 = createNode(1);
    struct Node* n2 = createNode(2);
    struct Node* n3 = createNode(3);
    struct Node* n4 = createNode(4);
    struct Node* n5 = createNode(5);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n3; // Creates cycle back to n3

    printf("--- Floyd's Cycle Detection and Entry Point ---\n\n");
    struct Node* cycleNode = detectCycleStart(n1);

    if (cycleNode != NULL) {
        printf("Result: Cycle DETECTED!\n");
        printf("Cycle begins at Node with data: %d\n", cycleNode->data);
    } else {
        printf("Result: NO cycle found.\n");
    }

    // Break cycle for proper cleanup
    n5->next = NULL;

    printf("\nTesting acyclic list after breaking loop:\n");
    struct Node* noCycle = detectCycleStart(n1);
    if (noCycle == NULL) {
        printf("Result: Verified - NO cycle exists.\n");
    }

    // Clean up
    free(n1); free(n2); free(n3); free(n4); free(n5);

    return 0;
}
