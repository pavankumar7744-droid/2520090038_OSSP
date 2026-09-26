#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 500
#define MAX_ARGS 50

int main() {
    char input[MAX];
    char *args[MAX_ARGS];
    int count = 0;

    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Error: Empty command\n");
        return 1;
    }

    char *token = strtok(input, " ");

    while (token != NULL && count < MAX_ARGS - 1) {
        args[count++] = token;
        token = strtok(NULL, " ");
    }

    args[count] = NULL;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {

        printf("Child PID: %d\n", getpid());

        execvp(args[0], args);

        perror("execvp");
        exit(1);
    }

    else {

        printf("Parent PID: %d\n", getpid());
        printf("Waiting for child...\n");

        int status;

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            printf("Child exited with status: %d\n",
                   WEXITSTATUS(status));
        else
            printf("Child terminated abnormally\n");
    }

    return 0;
}
