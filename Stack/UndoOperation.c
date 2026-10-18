#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_OPS 100
#define STR_LEN 128

typedef struct {
    char actions[MAX_OPS][STR_LEN];
    int top;
} UndoStack;

void init(UndoStack* s) {
    s->top = -1;
}

bool isEmpty(UndoStack* s) {
    return s->top == -1;
}

bool isFull(UndoStack* s) {
    return s->top == MAX_OPS - 1;
}

// Push an action onto the undo stack
void performAction(UndoStack* s, const char* action) {
    if (isFull(s)) {
        printf("Undo history is full!\n");
        return;
    }
    strncpy(s->actions[++(s->top)], action, STR_LEN - 1);
    s->actions[s->top][STR_LEN - 1] = '\0';
    printf("Action performed: \"%s\"\n", action);
}

// Undo the most recent action
void undo(UndoStack* s) {
    if (isEmpty(s)) {
        printf("Nothing to undo! Stack is empty.\n");
        return;
    }
    printf("Undo: Reverted \"%s\"\n", s->actions[(s->top)--]);
}

// Display current active action history
void displayHistory(UndoStack* s) {
    if (isEmpty(s)) {
        printf("Current Document State: [Empty]\n");
        return;
    }
    printf("Current Action Stack (most recent first):\n");
    for (int i = s->top; i >= 0; i--) {
        printf("  [%d] %s\n", i + 1, s->actions[i]);
    }
}

int main() {
    UndoStack editor;
    init(&editor);

    printf("--- Simulating Text Editor Undo Feature ---\n\n");

    performAction(&editor, "Type 'Hello'");
    performAction(&editor, "Type ' World'");
    performAction(&editor, "Bold selection 'World'");
    performAction(&editor, "Delete word 'World'");

    printf("\n");
    displayHistory(&editor);

    printf("\n--- Performing Undo Operations ---\n");
    undo(&editor);
    undo(&editor);

    printf("\n");
    displayHistory(&editor);

    printf("\n--- Performing New Action After Undo ---\n");
    performAction(&editor, "Type ' Everyone!'");

    printf("\n");
    displayHistory(&editor);

    printf("\n--- Undoing all actions ---\n");
    undo(&editor);
    undo(&editor);
    undo(&editor);
    undo(&editor); // Testing underflow

    return 0;
}
