#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_LEN 256

typedef struct PageNode {
    char url[URL_LEN];
    struct PageNode* prev;
    struct PageNode* next;
} PageNode;

typedef struct {
    PageNode* current;
} BrowserNavigation;

void initBrowser(BrowserNavigation* b) {
    b->current = NULL;
}

// Clear forward history beyond current page
void clearForwardHistory(PageNode* start) {
    PageNode* curr = start;
    while (curr != NULL) {
        PageNode* temp = curr->next;
        free(curr);
        curr = temp;
    }
}

// Visit a new page
void visit(BrowserNavigation* b, const char* url) {
    PageNode* newPage = (PageNode*)malloc(sizeof(PageNode));
    strncpy(newPage->url, url, URL_LEN - 1);
    newPage->url[URL_LEN - 1] = '\0';
    newPage->prev = NULL;
    newPage->next = NULL;

    if (b->current == NULL) {
        b->current = newPage;
    } else {
        // Discard all forward history
        if (b->current->next != NULL) {
            clearForwardHistory(b->current->next);
        }
        b->current->next = newPage;
        newPage->prev = b->current;
        b->current = newPage;
    }
    printf("Visited: %s\n", b->current->url);
}

// Navigate back
void back(BrowserNavigation* b) {
    if (b->current == NULL || b->current->prev == NULL) {
        printf("<- Cannot go back. No backward history.\n");
        return;
    }
    b->current = b->current->prev;
    printf("<- Back to: %s\n", b->current->url);
}

// Navigate forward
void forward(BrowserNavigation* b) {
    if (b->current == NULL || b->current->next == NULL) {
        printf("-> Cannot go forward. No forward history.\n");
        return;
    }
    b->current = b->current->next;
    printf("-> Forward to: %s\n", b->current->url);
}

// Display current page
void displayCurrentPage(BrowserNavigation* b) {
    if (b->current == NULL) {
        printf("Current Page: None (No page loaded)\n");
    } else {
        printf("Current Page: %s\n", b->current->url);
    }
}

int main() {
    BrowserNavigation browser;
    initBrowser(&browser);

    printf("--- Browser Forward/Backward Navigation using DLL ---\n\n");
    visit(&browser, "google.com");
    visit(&browser, "github.com");
    visit(&browser, "stackoverflow.com");
    visit(&browser, "reddit.com");

    printf("\n");
    displayCurrentPage(&browser);

    printf("\n--- Going Back ---\n");
    back(&browser);
    back(&browser);
    displayCurrentPage(&browser);

    printf("\n--- Going Forward ---\n");
    forward(&browser);
    displayCurrentPage(&browser);

    printf("\n--- Visiting new page from intermediate state ---\n");
    visit(&browser, "wikipedia.org"); // Clears forward history (reddit.com)
    displayCurrentPage(&browser);

    forward(&browser); // Should say cannot go forward
    back(&browser);
    displayCurrentPage(&browser);

    return 0;
}
