#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 10
#define BUFFER_SIZE 100

char *history[MAX_HISTORY];
int history_count = 0;
int history_pos = 0;

void add_history(const char *cmd) {
    if (history_count < MAX_HISTORY) {
        history[history_count] = malloc(strlen(cmd) + 1);
        strcpy(history[history_count], cmd);
        history_count++;
    } else {
        free(history[0]);

        for (int i = 1; i < MAX_HISTORY; i++)
            history[i - 1] = history[i];

        history[MAX_HISTORY - 1] = malloc(strlen(cmd) + 1);
        strcpy(history[MAX_HISTORY - 1], cmd);
    }

    history_pos = history_count;
}

void show_history() {
    printf("\nCommand History:\n");

    for (int i = 0; i < history_count; i++)
        printf("%d: %s\n", i + 1, history[i]);
}

void previous_command(char *buffer) {
    if (history_pos > 0) {
        history_pos--;
        strcpy(buffer, history[history_pos]);
    }
}

void next_command(char *buffer) {
    if (history_pos < history_count - 1) {
        history_pos++;
        strcpy(buffer, history[history_pos]);
    } else {
        history_pos = history_count;
        buffer[0] = '\0';
    }
}

int main() {
    char buffer[BUFFER_SIZE];

    printf("Simple Command History\n");
    printf("Type 'history', 'prev', 'next', or 'exit'\n");

    while (1) {
        printf("\n$ ");
        fgets(buffer, BUFFER_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        if (strcmp(buffer, "history") == 0) {
            show_history();
            continue;
        }

        if (strcmp(buffer, "prev") == 0) {
            previous_command(buffer);
            printf("Recalled: %s\n", buffer);
            continue;
        }

        if (strcmp(buffer, "next") == 0) {
            next_command(buffer);
            printf("Recalled: %s\n", buffer);
            continue;
        }

        if (strlen(buffer) > 0) {
            add_history(buffer);
            printf("Executed: %s\n", buffer);
        }
    }

    for (int i = 0; i < history_count; i++)
        free(history[i]);

    return 0;
}
