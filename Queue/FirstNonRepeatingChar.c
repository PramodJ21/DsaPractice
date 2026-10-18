#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 500

typedef struct {
    char items[MAX];
    int front;
    int rear;
} CharQueue;

void initQueue(CharQueue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(CharQueue* q) {
    return (q->front == -1 || q->front > q->rear);
}

void enqueue(CharQueue* q, char ch) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++(q->rear)] = ch;
}

char dequeue(CharQueue* q) {
    if (isEmpty(q)) return '\0';
    return q->items[q->front++];
}

char peekFront(CharQueue* q) {
    if (isEmpty(q)) return '\0';
    return q->items[q->front];
}

void processStream(const char* stream) {
    int freq[256] = {0};
    CharQueue q;
    initQueue(&q);

    printf("Input Stream: \"%s\"\n", stream);
    printf("%-10s %-20s %-20s\n", "Char Read", "First Non-Repeating", "Current Queue Front");
    printf("------------------------------------------------------------\n");

    for (int i = 0; stream[i] != '\0'; i++) {
        char ch = stream[i];
        freq[(unsigned char)ch]++;
        enqueue(&q, ch);

        // Discard characters from front of queue that have appeared more than once
        while (!isEmpty(&q) && freq[(unsigned char)peekFront(&q)] > 1) {
            dequeue(&q);
        }

        if (isEmpty(&q)) {
            printf("%-10c %-20s %-20s\n", ch, "None (-1)", "Empty");
        } else {
            char nonRep = peekFront(&q);
            printf("%-10c %-20c %-20c\n", ch, nonRep, nonRep);
        }
    }
    printf("\n");
}

int main() {
    processStream("aabc");
    processStream("abadbc");
    return 0;
}
