#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct SongNode {
    char title[64];
    char artist[64];
    int durationSec;
    struct SongNode* next;
} SongNode;

// Add song to playlist
void addSong(SongNode** head, const char* title, const char* artist, int durationSec) {
    SongNode* newNode = (SongNode*)malloc(sizeof(SongNode));
    strncpy(newNode->title, title, 63);
    newNode->title[63] = '\0';
    strncpy(newNode->artist, artist, 63);
    newNode->artist[63] = '\0';
    newNode->durationSec = durationSec;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        SongNode* curr = *head;
        while (curr->next != NULL) curr = curr->next;
        curr->next = newNode;
    }
    printf("Added Song: \"%s\" by %s (%d:%02d)\n", title, artist, durationSec / 60, durationSec % 60);
}

// Remove song by title
bool removeSong(SongNode** head, const char* title) {
    if (*head == NULL) {
        printf("Playlist is empty!\n");
        return false;
    }

    SongNode* curr = *head;
    SongNode* prev = NULL;

    // Check if head node holds the song
    if (strcasecmp(curr->title, title) == 0) {
        *head = curr->next;
        printf("Removed Song: \"%s\"\n", curr->title);
        free(curr);
        return true;
    }

    while (curr != NULL && strcasecmp(curr->title, title) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Song \"%s\" not found in playlist.\n", title);
        return false;
    }

    prev->next = curr->next;
    printf("Removed Song: \"%s\"\n", curr->title);
    free(curr);
    return true;
}

// Search for song by title
void searchSong(SongNode* head, const char* title) {
    SongNode* curr = head;
    int pos = 1;
    while (curr != NULL) {
        if (strcasecmp(curr->title, title) == 0) {
            printf("Found at Track #%d: \"%s\" by %s [%d:%02d]\n", 
                   pos, curr->title, curr->artist, curr->durationSec / 60, curr->durationSec % 60);
            return;
        }
        curr = curr->next;
        pos++;
    }
    printf("Song \"%s\" was not found in playlist.\n", title);
}

// Display playlist
void displayPlaylist(SongNode* head) {
    if (head == NULL) {
        printf("Playlist is currently empty.\n");
        return;
    }
    printf("\n=== Current Music Playlist ===\n");
    SongNode* curr = head;
    int track = 1;
    while (curr != NULL) {
        printf("  Track %d: %-25s | Artist: %-15s | %d:%02d\n", 
               track++, curr->title, curr->artist, curr->durationSec / 60, curr->durationSec % 60);
        curr = curr->next;
    }
    printf("==============================\n\n");
}

int main() {
    SongNode* playlist = NULL;

    printf("--- Music Playlist Manager (Singly Linked List) ---\n\n");
    addSong(&playlist, "Bohemian Rhapsody", "Queen", 354);
    addSong(&playlist, "Hotel California", "Eagles", 390);
    addSong(&playlist, "Shape of You", "Ed Sheeran", 233);
    addSong(&playlist, "Stairway to Heaven", "Led Zeppelin", 482);

    displayPlaylist(playlist);

    searchSong(playlist, "Hotel California");
    searchSong(playlist, "Imagine");

    printf("\n");
    removeSong(&playlist, "Shape of You");
    removeSong(&playlist, "Bohemian Rhapsody");

    displayPlaylist(playlist);

    return 0;
}
