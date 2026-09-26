#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent started. PID = %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child started. PID = %d\n", getpid());

        for (int i = 1; i <= 5; i++) {
            printf("Child working... %d\n", i);
            sleep(1);
        }

        printf("Child finished.\n");
        exit(42);
    }

    else {
        printf("Parent waiting for child %d...\n", pid);

        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("Child exited normally.\n");
            printf("Exit status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n",
                   WTERMSIG(status));
        }

        printf("Parent continues after child completion.\n");
    }

    return 0;
}
