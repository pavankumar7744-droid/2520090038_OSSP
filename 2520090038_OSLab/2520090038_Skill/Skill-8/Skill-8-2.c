#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 500
#define MAX_ARGS 50

typedef void (*CommandFunction)(char **);

void builtin_pwd(char **args) {
    char cwd[1000];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

void builtin_cd(char **args) {
    if (args[1] == NULL) {
        printf("cd: missing argument\n");
        return;
    }

    if (chdir(args[1]) != 0)
        perror("cd");
}

void builtin_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s", args[i]);

        if (args[i + 1] != NULL)
            printf(" ");
    }

    printf("\n");
}

void builtin_help(char **args) {
    printf("Built-in commands:\n");
    printf("  cd <directory>\n");
    printf("  pwd\n");
    printf("  echo <text>\n");
    printf("  help\n");
    printf("  exit\n");
}

void builtin_exit(char **args) {
    printf("Exiting shell...\n");
    exit(0);
}

typedef struct {
    char *name;
    CommandFunction function;
} Command;

Command command_table[] = {
    {"cd", builtin_cd},
    {"pwd", builtin_pwd},
    {"echo", builtin_echo},
    {"help", builtin_help},
    {"exit", builtin_exit},
    {NULL, NULL}
};

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {

        printf("myshell$ ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        int count = 0;

        char *token = strtok(input, " ");

        while (token != NULL && count < MAX_ARGS - 1) {
            args[count++] = token;
            token = strtok(NULL, " ");
        }

        args[count] = NULL;

        int found = 0;

        for (int i = 0; command_table[i].name != NULL; i++) {

            if (strcmp(args[0], command_table[i].name) == 0) {

                command_table[i].function(args);
                found = 1;
                break;
            }
        }

        if (!found)
            printf("myshell: command not found: %s\n", args[0]);
    }

    return 0;
}
