#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Coach {
    char coachId[16];   // e.g. "B1", "A2", "S3", "ENG"
    char coachType[32]; // e.g. "Sleeper", "AC 3 Tier", "Engine"
    struct Coach* prev;
    struct Coach* next;
} Coach;

typedef struct {
    Coach* head; // Engine end
    Coach* tail; // Guard end
} Train;

void initTrain(Train* t) {
    t->head = NULL;
    t->tail = NULL;
}

// Add coach at 1-based position
void addCoachAtPosition(Train* t, const char* coachId, const char* coachType, int pos) {
    if (pos < 1) {
        printf("Invalid position %d! Must be >= 1.\n", pos);
        return;
    }

    Coach* newCoach = (Coach*)malloc(sizeof(Coach));
    strncpy(newCoach->coachId, coachId, 15);
    newCoach->coachId[15] = '\0';
    strncpy(newCoach->coachType, coachType, 31);
    newCoach->coachType[31] = '\0';
    newCoach->prev = NULL;
    newCoach->next = NULL;

    // Case 1: Insert at beginning (pos 1)
    if (pos == 1) {
        newCoach->next = t->head;
        if (t->head != NULL) {
            t->head->prev = newCoach;
        } else {
            t->tail = newCoach;
        }
        t->head = newCoach;
        printf("Attached Coach [%s: %s] at position 1\n", coachId, coachType);
        return;
    }

    Coach* curr = t->head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Position %d is out of bounds! Appending to the end of train.\n", pos);
        // Attach at tail
        if (t->tail != NULL) {
            t->tail->next = newCoach;
            newCoach->prev = t->tail;
            t->tail = newCoach;
        } else {
            t->head = newCoach;
            t->tail = newCoach;
        }
        return;
    }

    newCoach->next = curr->next;
    newCoach->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = newCoach;
    } else {
        t->tail = newCoach;
    }
    curr->next = newCoach;
    printf("Attached Coach [%s: %s] at position %d\n", coachId, coachType, pos);
}

// Remove coach by ID
bool removeCoach(Train* t, const char* coachId) {
    if (t->head == NULL) {
        printf("Train has no coaches attached!\n");
        return false;
    }

    Coach* curr = t->head;
    while (curr != NULL && strcmp(curr->coachId, coachId) != 0) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Coach \"%s\" not found in train configuration.\n", coachId);
        return false;
    }

    if (curr->prev != NULL) curr->prev->next = curr->next;
    else t->head = curr->next;

    if (curr->next != NULL) curr->next->prev = curr->prev;
    else t->tail = curr->prev;

    printf("Decoupled Coach [%s: %s]\n", curr->coachId, curr->coachType);
    free(curr);
    return true;
}

// Display coaches Engine to Guard (head to tail)
void displayForward(Train* t) {
    printf("Engine -> Guard: ");
    Coach* curr = t->head;
    while (curr != NULL) {
        printf("[%s] ", curr->coachId);
        if (curr->next != NULL) printf("<==> ");
        curr = curr->next;
    }
    printf("\n");
}

// Display coaches Guard to Engine (tail to head)
void displayReverse(Train* t) {
    printf("Guard -> Engine: ");
    Coach* curr = t->tail;
    while (curr != NULL) {
        printf("[%s] ", curr->coachId);
        if (curr->prev != NULL) printf("<==> ");
        curr = curr->prev;
    }
    printf("\n");
}

int main() {
    Train train;
    initTrain(&train);

    printf("--- Train Coach Management System (DLL) ---\n\n");
    addCoachAtPosition(&train, "ENG", "Locomotive Engine", 1);
    addCoachAtPosition(&train, "GEN1", "General Unreserved", 2);
    addCoachAtPosition(&train, "S1", "Sleeper Class", 3);
    addCoachAtPosition(&train, "S2", "Sleeper Class", 4);
    addCoachAtPosition(&train, "B1", "AC 3-Tier", 5);

    printf("\n");
    displayForward(&train);
    displayReverse(&train);

    printf("\n--- Inserting VIP Pantry Coach at Position 3 ---\n");
    addCoachAtPosition(&train, "PC", "Pantry Car", 3);
    displayForward(&train);

    printf("\n--- Decoupling Defective Coach S1 ---\n");
    removeCoach(&train, "S1");
    displayForward(&train);
    displayReverse(&train);

    return 0;
}
