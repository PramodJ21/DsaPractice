#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define URL_LEN 256

typedef struct {
    char urls[MAX_PAGES][URL_LEN];
    int top;
} HistoryStack;

void initStack(HistoryStack* s) {
    s->top = -1;
}

bool isEmpty(HistoryStack* s) {
    return s->top == -1;
}

void push(HistoryStack* s, const char* url) {
    if (s->top < MAX_PAGES - 1) {
        strncpy(s->urls[++(s->top)], url, URL_LEN - 1);
        s->urls[s->top][URL_LEN - 1] = '\0';
    }
}

char* pop(HistoryStack* s) {
    if (!isEmpty(s)) {
        return s->urls[(s->top)--];
    }
    return NULL;
}

typedef struct {
    char currentPage[URL_LEN];
    bool hasCurrentPage;
    HistoryStack backStack;
} Browser;

void initBrowser(Browser* b) {
    b->hasCurrentPage = false;
    b->currentPage[0] = '\0';
    initStack(&b->backStack);
}

// Visit a new page
void visit(Browser* b, const char* url) {
    if (b->hasCurrentPage) {
        push(&b->backStack, b->currentPage);
    }
    strncpy(b->currentPage, url, URL_LEN - 1);
    b->currentPage[URL_LEN - 1] = '\0';
    b->hasCurrentPage = true;
    printf("Visited: %s\n", b->currentPage);
}

// Go back to the previous page
void back(Browser* b) {
    if (isEmpty(&b->backStack)) {
        printf("Cannot go back. No previous history!\n");
        return;
    }
    char* prev = pop(&b->backStack);
    strncpy(b->currentPage, prev, URL_LEN - 1);
    b->currentPage[URL_LEN - 1] = '\0';
    printf("Went back to: %s\n", b->currentPage);
}

// Display the current page
void displayCurrentPage(Browser* b) {
    if (!b->hasCurrentPage) {
        printf("No page currently open.\n");
    } else {
        printf("Current Page: %s\n", b->currentPage);
    }
}

int main() {
    Browser browser;
    initBrowser(&browser);

    printf("--- Browser History Simulation ---\n\n");

    displayCurrentPage(&browser);

    visit(&browser, "https://google.com");
    displayCurrentPage(&browser);

    visit(&browser, "https://github.com");
    visit(&browser, "https://stackoverflow.com");
    visit(&browser, "https://en.wikipedia.org");
    displayCurrentPage(&browser);

    printf("\n--- Navigating Back ---\n");
    back(&browser);
    displayCurrentPage(&browser);

    back(&browser);
    displayCurrentPage(&browser);

    visit(&browser, "https://reddit.com");
    displayCurrentPage(&browser);

    back(&browser);
    displayCurrentPage(&browser);

    back(&browser);
    displayCurrentPage(&browser);

    back(&browser); // Underflow test

    return 0;
}
