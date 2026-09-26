#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH 4096
#define MAX_CMD 256

int main() {
    char command[MAX_CMD];
    char *path;
    char *path_copy;
    char *dir;

    printf("Enter command: ");
    scanf("%255s", command);

    /* Retrieve PATH */
    path = getenv("PATH");

    if (path == NULL) {
        printf("PATH variable not found.\n");
        return 1;
    }

    printf("\nPATH = %s\n", path);

    /* Make a copy because strtok modifies the string */
    path_copy = malloc(strlen(path) + 1);

    if (path_copy == NULL) {
        perror("malloc");
        return 1;
    }

    strcpy(path_copy, path);

    /* Parse PATH directories */
    dir = strtok(path_copy, ":");

    while (dir != NULL) {

        char full_path[MAX_PATH];

        snprintf(full_path, sizeof(full_path),
                 "%s/%s", dir, command);

        /* Check whether file exists */
        if (access(full_path, F_OK) == 0) {

            /* Check execute permission */
            if (access(full_path, X_OK) == 0) {
                printf("\nCommand found!\n");
                printf("Executable: %s\n", full_path);

                free(path_copy);
                return 0;
            }
            else {
                printf("\nFound but not executable:\n");
                printf("%s\n", full_path);

                free(path_copy);
                return 1;
            }
        }

        dir = strtok(NULL, ":");
    }

    printf("\nCommand '%s' not found in PATH.\n", command);

    free(path_copy);

    return 1;
}
