#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_CAPACITY 3

/* ============================================================
   1. ARRAY-BASED STACK (Static Memory, Bounded Size)
   ============================================================ */
typedef struct {
    int arr[ARRAY_CAPACITY];
    int top;
} ArrayStack;

void initArrayStack(ArrayStack* s) { s->top = -1; }
bool isArrayStackFull(ArrayStack* s) { return s->top == ARRAY_CAPACITY - 1; }
bool isArrayStackEmpty(ArrayStack* s) { return s->top == -1; }

void pushArrayStack(ArrayStack* s, int val) {
    if (isArrayStackFull(s)) {
        printf("  [ArrayStack OVERFLOW!] Hard capacity of %d reached. Cannot push %d\n", 
               ARRAY_CAPACITY, val);
        return;
    }
    s->arr[++(s->top)] = val;
    printf("  [ArrayStack Pushed %d] top = %d (Contiguous buffer at index %d)\n", val, s->top, s->top);
}

/* ============================================================
   2. LINKED-LIST-BASED STACK (Dynamic Heap Allocation, Unbounded)
   ============================================================ */
struct LLNode {
    int data;
    struct LLNode* next;
};

void pushLLStack(struct LLNode** top, int val) {
    struct LLNode* newNode = (struct LLNode*)malloc(sizeof(struct LLNode));
    if (newNode == NULL) {
        printf("  [LLStack Heap Exhaustion!] System out of memory.\n");
        return;
    }
    newNode->data = val;
    newNode->next = *top;
    *top = newNode;
    printf("  [LLStack Pushed %d] Dynamic heap allocation at address: %p (8/16 bytes overhead)\n", 
           val, (void*)newNode);
}

/* ============================================================
   3. DEMONSTRATION & COMPARISON
   ============================================================ */
int main() {
    printf("==================================================================\n");
    printf("  COMPARATIVE STUDY: ARRAY-BASED VS LINKED-LIST-BASED STRUCTURES  \n");
    printf("==================================================================\n\n");

    printf("--- PART 1: Demonstrating Array-based Fixed Capacity & Overflow ---\n");
    printf("Array Stack initialized with fixed capacity = %d elements.\n", ARRAY_CAPACITY);
    ArrayStack arrStack;
    initArrayStack(&arrStack);

    pushArrayStack(&arrStack, 10);
    pushArrayStack(&arrStack, 20);
    pushArrayStack(&arrStack, 30);
    // Pushing 4th element triggers hard overflow
    pushArrayStack(&arrStack, 40);

    printf("\n--- PART 2: Demonstrating Linked-List Dynamic Allocation Behavior ---\n");
    printf("Linked-List Stack has NO fixed upper bound; dynamically expands via heap malloc.\n");
    struct LLNode* llStack = NULL;

    pushLLStack(&llStack, 10);
    pushLLStack(&llStack, 20);
    pushLLStack(&llStack, 30);
    // Linked list seamlessly allocates 4th and 5th elements
    pushLLStack(&llStack, 40);
    pushLLStack(&llStack, 50);

    printf("\n==================================================================\n");
    printf("                    ARCHITECTURAL COMPARISON                      \n");
    printf("==================================================================\n");
    printf("%-20s %-25s %-25s\n", "Feature", "Array Implementation", "Linked List Implementation");
    printf("------------------------------------------------------------------\n");
    printf("%-20s %-25s %-25s\n", "Memory Allocation", "Contiguous static block", "Non-contiguous dynamic heap");
    printf("%-20s %-25s %-25s\n", "Capacity Limit", "Fixed (triggers Overflow)", "Dynamic (limited by RAM)");
    printf("%-20s %-25s %-25s\n", "Memory Overhead", "0 extra pointer bytes", "Extra 'next' pointer per node");
    printf("%-20s %-25s %-25s\n", "Cache Locality", "High (CPU cache friendly)", "Low (pointer chasing)");
    printf("%-20s %-25s %-25s\n", "Push/Pop Time", "O(1) directly in index", "O(1) with malloc/free overhead");
    printf("==================================================================\n");

    // Clean up dynamic heap nodes
    while (llStack != NULL) {
        struct LLNode* temp = llStack;
        llStack = llStack->next;
        free(temp);
    }

    return 0;
}
