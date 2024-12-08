#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONGS 100
#define MAX_TITLE_LENGTH 100
#define MAX_GENRE_LENGTH 50

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char artist[MAX_TITLE_LENGTH];
    char genre[MAX_GENRE_LENGTH];
} Song;

typedef struct {
    Song songs[MAX_SONGS];
    int count;
    int currentSongIndex;
} Playlist;

void initializePlaylist(Playlist *playlist) {
    playlist->count = 0;
    playlist->currentSongIndex = -1;
}

void addSong(Playlist *playlist, const char *title, const char *artist, const char *genre) {
    if (playlist->count < MAX_SONGS) {
        strcpy(playlist->songs[playlist->count].title, title);
        strcpy(playlist->songs[playlist->count].artist, artist);
        strcpy(playlist->songs[playlist->count].genre, genre);
        playlist->count++;
        printf("Added: %s by %s [%s]\n", title, artist, genre);
    } else {
        printf("Playlist is full!\n");
    }
}

void playNext(Playlist *playlist) {
    if (playlist->count == 0) {
        printf("No songs in the playlist.\n");
        return;
    }
    playlist->currentSongIndex = (playlist->currentSongIndex + 1) % playlist->count;
    printf("Playing: %s by %s [%s]\n", playlist->songs[playlist->currentSongIndex].title,
           playlist->songs[playlist->currentSongIndex].artist,
           playlist->songs[playlist->currentSongIndex].genre);
}

void playPrevious(Playlist *playlist) {
    if (playlist->count == 0) {
        printf("No songs in the playlist.\n");
        return;
    }
    playlist->currentSongIndex = (playlist->currentSongIndex - 1 + playlist->count) % playlist->count;
    printf("Playing: %s by %s [%s]\n", playlist->songs[playlist->currentSongIndex].title,
           playlist->songs[playlist->currentSongIndex].artist,
           playlist->songs[playlist->currentSongIndex].genre);
}

void switchToSong(Playlist *playlist, int index) {
    if (index < 0 || index >= playlist->count) {
        printf("Invalid song index!\n");
        return;
    }
    playlist->currentSongIndex = index;
    printf("Playing: %s by %s [%s]\n", playlist->songs[playlist->currentSongIndex].title,
           playlist->songs[playlist->currentSongIndex].artist,
           playlist->songs[playlist->currentSongIndex].genre);
}

void displaySongsByGenre(Playlist *playlist, const char *genre) {
    printf("Songs in genre: %s\n", genre);
    for (int i = 0; i < playlist->count; i++) {
        if (strcmp(playlist->songs[i].genre, genre) == 0) {
            printf("%d: %s by %s\n", i, playlist->songs[i].title, playlist->songs[i].artist);
        }
    }
}

void displayPlaylist(Playlist *playlist) {
    printf("Playlist:\n");
    for (int i = 0; i < playlist->count; i++) {
        printf("%d: %s by %s [%s]\n", i, playlist->songs[i].title, playlist->songs[i].artist, playlist->songs[i].genre);
    }
}

int main() {
    Playlist playlist;
    initializePlaylist(&playlist);

    int choice;
    char title[MAX_TITLE_LENGTH], artist[MAX_TITLE_LENGTH], genre[MAX_GENRE_LENGTH];
    int index;

    do {
        printf("\nMusic Playlist System\n");
        printf("1. Add Song\n");
        printf("2. Play Next Song\n");
        printf("3. Play Previous Song\n");
        printf("4. Switch to Song\n");
        printf("5. Display Songs by Genre\n");
        printf("6. Display Playlist\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                fgets(title, MAX_TITLE_LENGTH, stdin);
                title[strcspn(title, "\n")] = 0; // Remove newline character
                printf("Enter artist name: ");
                fgets(artist, MAX_TITLE_LENGTH, stdin);
                artist[strcspn(artist, "\n")] = 0; // Remove newline character
                printf("Enter genre: ");
                fgets(genre, MAX_GENRE_LENGTH, stdin);
                genre[strcspn(genre, "\n")] = 0; // Remove newline character
                addSong(&playlist, title, artist, genre);
                break;
            case 2:
                playNext(&playlist);
                break;
            case 3:
                playPrevious(&playlist);
                break;
            case 4:
                printf("Enter song index to switch to: ");
                scanf("%d", &index);
                switchToSong(&playlist, index);
                break;
            case 5:
                printf("Enter genre to display: ");
                fgets(genre, MAX_GENRE_LENGTH, stdin);
                genre[strcspn(genre, "\n")] = 0; // Remove newline character
                displaySongsByGenre(&playlist, genre);
                break;
            case 6:
                displayPlaylist(&playlist);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}