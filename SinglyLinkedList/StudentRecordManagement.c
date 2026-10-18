#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct StudentNode {
    int rollNo;
    char name[50];
    float marks;
    struct StudentNode* next;
} StudentNode;

// Insert student record at end
void insertStudent(StudentNode** head, int rollNo, const char* name, float marks) {
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
    newNode->rollNo = rollNo;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';
    newNode->marks = marks;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        StudentNode* curr = *head;
        while (curr->next != NULL) curr = curr->next;
        curr->next = newNode;
    }
    printf("Inserted Record: Roll %d, %s, Marks: %.2f\n", rollNo, name, marks);
}

// Delete student record by roll number
bool deleteByRoll(StudentNode** head, int rollNo) {
    if (*head == NULL) {
        printf("Record database is empty!\n");
        return false;
    }

    StudentNode* curr = *head;
    StudentNode* prev = NULL;

    if (curr->rollNo == rollNo) {
        *head = curr->next;
        printf("Deleted Record for Roll #%d (%s)\n", rollNo, curr->name);
        free(curr);
        return true;
    }

    while (curr != NULL && curr->rollNo != rollNo) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Student with Roll #%d not found!\n", rollNo);
        return false;
    }

    prev->next = curr->next;
    printf("Deleted Record for Roll #%d (%s)\n", rollNo, curr->name);
    free(curr);
    return true;
}

// Search student by roll number
void searchStudent(StudentNode* head, int rollNo) {
    StudentNode* curr = head;
    while (curr != NULL) {
        if (curr->rollNo == rollNo) {
            printf("Found Record: Roll %d | Name: %-15s | Marks: %.2f\n", 
                   curr->rollNo, curr->name, curr->marks);
            return;
        }
        curr = curr->next;
    }
    printf("Student with Roll #%d not found.\n", rollNo);
}

// Find student with highest marks
void findHighestScorer(StudentNode* head) {
    if (head == NULL) {
        printf("No student records available.\n");
        return;
    }

    StudentNode* highest = head;
    StudentNode* curr = head->next;

    while (curr != NULL) {
        if (curr->marks > highest->marks) {
            highest = curr;
        }
        curr = curr->next;
    }

    printf("\nTop Scorer: %s (Roll #%d) with Marks: %.2f\n\n", 
           highest->name, highest->rollNo, highest->marks);
}

// Display all student records
void displayRecords(StudentNode* head) {
    if (head == NULL) {
        printf("No student records to display.\n");
        return;
    }
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Student Name", "Marks");
    printf("-----------------------------------------\n");
    StudentNode* curr = head;
    while (curr != NULL) {
        printf("%-10d %-20s %-10.2f\n", curr->rollNo, curr->name, curr->marks);
        curr = curr->next;
    }
    printf("-----------------------------------------\n");
}

int main() {
    StudentNode* db = NULL;

    printf("--- Student Record Management System ---\n\n");
    insertStudent(&db, 101, "Alice Smith", 88.5f);
    insertStudent(&db, 102, "Bob Johnson", 94.0f);
    insertStudent(&db, 103, "Charlie Brown", 76.5f);
    insertStudent(&db, 104, "Diana Prince", 98.2f);
    insertStudent(&db, 105, "Edward Cullen", 82.0f);

    displayRecords(db);

    findHighestScorer(db);

    searchStudent(db, 103);
    searchStudent(db, 199);

    printf("\n");
    deleteByRoll(&db, 103);
    deleteByRoll(&db, 101);

    displayRecords(db);

    return 0;
}
