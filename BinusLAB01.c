#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct song { char title[100], artist[100]; int duration; };
struct playlist { char name[100]; int songCount; struct song songs[1000]; } playlists[1000];
int playlistCount = 0, input = 0;

void mergesortplaylist(int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergesortplaylist(left, mid); mergesortplaylist(mid + 1, right);
        int leftSize = mid - left + 1, rightSize = right - mid;
        struct playlist leftPlaylist[leftSize], rightPlaylist[rightSize];
        for (int i = 0; i < leftSize; i++) leftPlaylist[i] = playlists[left + i];
        for (int i = 0; i < rightSize; i++) rightPlaylist[i] = playlists[mid + 1 + i];
        int i = 0, j = 0, k = left;
        while (i < leftSize && j < rightSize)
        {
            if (strcmp(leftPlaylist[i].name, rightPlaylist[j].name) <= 0) { playlists[k] = leftPlaylist[i]; i++; }
            else { playlists[k] = rightPlaylist[j]; j++; }
            k++;
        }
        while (i < leftSize) { playlists[k] = leftPlaylist[i]; i++; k++; }
        while (j < rightSize) { playlists[k] = rightPlaylist[j]; j++; k++; }
    }
}

void qsortplaylist(int left, int right)
{
    if (left < right)
    {
        char pivot[100]; strcpy(pivot, playlists[right].name);
        int i = left - 1, j = left;
        while (j < right)
        {
            if (strcmpi(playlists[j].name, pivot) < 0)
            {
                i++;
                struct playlist temp = playlists[i]; playlists[i] = playlists[j]; playlists[j] = temp;
            } j++;
        }
        struct playlist temp = playlists[i + 1];
        playlists[i + 1] = playlists[right]; playlists[right] = temp; int partition = i + 1;
        qsortplaylist(left, partition - 1); qsortplaylist(partition + 1, right);
    }
}

void mergesortsong(int left, int right, int playlistIndex)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergesortsong(left, mid, playlistIndex); mergesortsong(mid + 1, right, playlistIndex);
        int leftSize = mid - left + 1, rightSize = right - mid;
        struct song leftSong[leftSize], rightSong[rightSize];
        for (int i = 0; i < leftSize; i++) leftSong[i] = playlists[playlistIndex].songs[left + i];
        for (int i = 0; i < rightSize; i++) rightSong[i] = playlists[playlistIndex].songs[mid + 1 + i];
        int i = 0, j = 0, k = left;
        while (i < leftSize && j < rightSize)
        {
            if (strcmp(leftSong[i].title, rightSong[j].title) <= 0) { playlists[playlistIndex].songs[k] = leftSong[i]; i++; }
            else { playlists[playlistIndex].songs[k] = rightSong[j]; j++; }
            k++;
        }
        while (i < leftSize) { playlists[playlistIndex].songs[k] = leftSong[i]; i++; k++; }
        while (j < rightSize) { playlists[playlistIndex].songs[k] = rightSong[j]; j++; k++; }
    }
}

void qsortsong(int left, int right, int playlistIndex)
{
    if (left < right)
    {
        char pivot[100]; strcpy(pivot, playlists[playlistIndex].songs[right].title);
        int i = left - 1, j = left;
        while (j < right)
        {
            if (strcmpi(playlists[playlistIndex].songs[j].title, pivot) < 0)
            {
                i++;
                struct song temp = playlists[playlistIndex].songs[i]; playlists[playlistIndex].songs[i] = playlists[playlistIndex].songs[j]; playlists[playlistIndex].songs[j] = temp;
            } j++;
        }
        struct song temp = playlists[playlistIndex].songs[i + 1];
        playlists[playlistIndex].songs[i + 1] = playlists[playlistIndex].songs[right]; playlists[playlistIndex].songs[right] = temp; int partition = i + 1;
        qsortsong(left, partition - 1, playlistIndex); qsortsong(partition + 1, right, playlistIndex);
    }
}

int searchplaylist(char playlistName[])
{
    if (!playlistCount) return -1;
    int left = 0, right = playlistCount - 1;
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (strcmpi(playlists[middle].name, playlistName) == 0) return middle;
        else if (strcmpi(playlists[middle].name, playlistName) < 0) left = middle + 1;
        else right = middle - 1;
    }
    return -1;
}

int searchsong(char songName[], int location)
{
    if (!playlists[location].songCount) return -1;
    int left = 0, right = playlists[location].songCount - 1;
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (strcmpi(playlists[location].songs[middle].title, songName) == 0) return middle;
        else if (strcmpi(playlists[location].songs[middle].title, songName) < 0) left = middle + 1;
        else right = middle - 1;
    }
    return -1;
}

void addsong(char songTitle[], char songArtist[], int songDuration, char playlistName[])
{
    if (searchplaylist(playlistName) == -1)
    {
        playlists[playlistCount].songCount = 0;
        strcpy(playlists[playlistCount].name, playlistName);
        strcpy(playlists[playlistCount].songs[playlists[playlistCount].songCount].title, songTitle);
        strcpy(playlists[playlistCount].songs[playlists[playlistCount].songCount].artist, songArtist);
        playlists[playlistCount].songs[playlists[playlistCount].songCount].duration = songDuration;
        playlists[playlistCount].songCount++; playlistCount++;
        // qsortplaylist(0, playlistCount - 1);
        mergesortplaylist(0, playlistCount - 1);
    }
    else
    {
        int location = searchplaylist(playlistName);
        if (searchsong(songTitle, location) != -1) return;
        strcpy(playlists[location].songs[playlists[location].songCount].title, songTitle);
        strcpy(playlists[location].songs[playlists[location].songCount].artist, songArtist);
        playlists[location].songs[playlists[location].songCount].duration = songDuration;
        playlists[location].songCount++;
        // qsortsong(0, playlists[location].songCount - 1, location);
        mergesortsong(0, playlists[location].songCount - 1, location);
    }
}

void menu_display()
{
    system("cls");
    printf("Song Player      \n");
    printf("=================\n");
    printf("1. Add new song  \n");
    printf("2. Show all songs\n");
    printf("3. Search song(s)\n");
    printf("4. Exit          \n");
    printf("Choose >> "); scanf("%d", &input); getchar();
}

void menu_3()
{
    char songName[100] = {}, current[100] = {}; int found = 0;
    while (strlen(songName) <= 0) { printf("Song to search: "); gets(songName); }
    for (int i = 0; i < playlistCount; i++)
    {
        int detected = 0;
        for (int j = 0; j < playlists[i].songCount; j++)
        {
            strcpy(current, playlists[i].songs[j].title);
            if (strstr(strlwr(current), strlwr(songName)) != NULL)
            {
                if (!detected)
                {
                    printf("================================================================================\n");
                    printf("| >> Playlist %03d: %-59s |\n", i + 1, playlists[i].name);
                    printf("================================================================================\n");
                    detected = 1;
                }
                found = 1;
                printf("| %03d | %25s | %23s | %8d seconds |\n", j + 1, playlists[i].songs[j].title, playlists[i].songs[j].artist, playlists[i].songs[j].duration);
            }
        }
    }
    if (!found) printf("No song found!\n");
    else printf("================================================================================\n");
    printf("Press any key to continue... "); getch();
}

void menu_2()
{
    printf("================================================================================\n");
    if (!playlistCount) printf("No playlist found!\n");
    else
    {
        for (int i = 0; i < playlistCount; i++)
        {
            printf("================================================================================\n");
            printf("| >> Playlist %03d: %-59s |\n", i + 1, playlists[i].name);
            printf("================================================================================\n");
            for (int j = 0; j < playlists[i].songCount; j++)
            {
                printf("| %03d | %25s | %23s | %8d seconds |\n", j + 1, playlists[i].songs[j].title, playlists[i].songs[j].artist, playlists[i].songs[j].duration);
            }
        }
    }
    printf("================================================================================\n");
    printf("Press any key to continue... "); getch();
}

void menu_1()
{
    char songTitle[100] = {}, songArtist[100] = {}, playlistName[100] = {}; int songDuration = 0;
    while (strlen(songTitle) <= 0) { printf("Song Name [must not be empty]                : "); gets(songTitle); }
    while (strlen(songArtist) <= 0) { printf("Song Artist [must not be empty]              : "); gets(songArtist); }
    while (songDuration <= 0) { printf("Song Duration (in seconds) [must be positive]: "); scanf("%d", &songDuration); getchar(); }
    while (strlen(playlistName) <= 0) { printf("Playlist Name [must not be empty]            : "); gets(playlistName); }
    addsong(songTitle, songArtist, songDuration, playlistName);
    printf("Added... "); getch();
}

void importsongs()
{
    FILE *database = fopen("testdata.in", "r");
    char check = fgetc(fp);
    if (check == EOF) return;
    else ungetc(check, fp);
    while(!feof(database))
    {
        char songTitle[100], songArtist[100], playlistName[100]; int songDuration = 0;
        fscanf(database, "%[^#]#%[^#]#%d#%[^\n]\n", songTitle, songArtist, &songDuration, playlistName);
        addsong(songTitle, songArtist, songDuration, playlistName);
    }
    fclose(database);
}

void writesongs()
{
    FILE *database = fopen("testdata.in", "w");
    for (int i = 0; i < playlistCount; i++)
    {
        for (int j = 0; j < playlists[i].songCount; j++)
        {
            fprintf(database, "%s#%s#%d#%s\n", playlists[i].songs[j].title, playlists[i].songs[j].artist, playlists[i].songs[j].duration, playlists[i].name);
        }
    }
    fclose(database);
}

int main()
{
    importsongs();
    while (input != 4)
    {
        menu_display();
        switch (input)
        {
            case 1: menu_1(); break;
            case 2: menu_2(); break;
            case 3: menu_3(); break;
        }
    }
    writesongs();
}