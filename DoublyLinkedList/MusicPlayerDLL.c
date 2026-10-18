#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Song {
    char title[64];
    char artist[64];
    struct Song* prev;
    struct Song* next;
} Song;

typedef struct {
    Song* head;
    Song* tail;
    Song* current;
} MusicPlayer;

void initPlayer(MusicPlayer* mp) {
    mp->head = NULL;
    mp->tail = NULL;
    mp->current = NULL;
}

// Add song to playlist end
void addSong(MusicPlayer* mp, const char* title, const char* artist) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strncpy(newSong->title, title, 63);
    newSong->title[63] = '\0';
    strncpy(newSong->artist, artist, 63);
    newSong->artist[63] = '\0';
    newSong->prev = mp->tail;
    newSong->next = NULL;

    if (mp->tail != NULL) {
        mp->tail->next = newSong;
    } else {
        mp->head = newSong;
        mp->current = newSong; // Start on first song
    }
    mp->tail = newSong;
    printf("Added: \"%s\" by %s\n", title, artist);
}

// Remove song by title
bool removeSong(MusicPlayer* mp, const char* title) {
    if (mp->head == NULL) {
        printf("Playlist is empty!\n");
        return false;
    }

    Song* curr = mp->head;
    while (curr != NULL && strcasecmp(curr->title, title) != 0) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Song \"%s\" not found in playlist.\n", title);
        return false;
    }

    // If deleting currently playing song, advance or go to prev
    if (mp->current == curr) {
        if (curr->next != NULL) mp->current = curr->next;
        else mp->current = curr->prev;
    }

    if (curr->prev != NULL) curr->prev->next = curr->next;
    else mp->head = curr->next;

    if (curr->next != NULL) curr->next->prev = curr->prev;
    else mp->tail = curr->prev;

    printf("Removed: \"%s\"\n", curr->title);
    free(curr);
    return true;
}

// Move to next song (bounded: prevents navigation beyond end)
void nextSong(MusicPlayer* mp) {
    if (mp->current == NULL) {
        printf("No song is currently selected.\n");
        return;
    }
    if (mp->current->next == NULL) {
        printf("End of playlist reached! Cannot play next song.\n");
        return;
    }
    mp->current = mp->current->next;
    printf(">> Now Playing: \"%s\" by %s\n", mp->current->title, mp->current->artist);
}

// Move to previous song (bounded: prevents navigation beyond start)
void previousSong(MusicPlayer* mp) {
    if (mp->current == NULL) {
        printf("No song is currently selected.\n");
        return;
    }
    if (mp->current->prev == NULL) {
        printf("Start of playlist reached! Cannot play previous song.\n");
        return;
    }
    mp->current = mp->current->prev;
    printf("<< Now Playing: \"%s\" by %s\n", mp->current->title, mp->current->artist);
}

// Display playlist and highlight current song
void displayPlaylist(MusicPlayer* mp) {
    if (mp->head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    printf("\n--- Playlist Tracks ---\n");
    Song* curr = mp->head;
    int idx = 1;
    while (curr != NULL) {
        if (curr == mp->current) {
            printf("  -> [%d] %-25s | %-15s (CURRENTLY PLAYING)\n", idx++, curr->title, curr->artist);
        } else {
            printf("     [%d] %-25s | %-15s\n", idx++, curr->title, curr->artist);
        }
        curr = curr->next;
    }
    printf("-----------------------\n\n");
}

int main() {
    MusicPlayer player;
    initPlayer(&player);

    printf("--- Music Player Simulation (Non-Circular DLL) ---\n\n");
    addSong(&player, "Viva La Vida", "Coldplay");
    addSong(&player, "Rolling in the Deep", "Adele");
    addSong(&player, "Blinding Lights", "The Weeknd");

    displayPlaylist(&player);

    // Try going backward from first song (boundary check)
    previousSong(&player);

    // Navigate forward
    nextSong(&player);
    nextSong(&player);

    // Try going forward beyond end (boundary check)
    nextSong(&player);

    displayPlaylist(&player);

    removeSong(&player, "Rolling in the Deep");
    displayPlaylist(&player);

    return 0;
}
