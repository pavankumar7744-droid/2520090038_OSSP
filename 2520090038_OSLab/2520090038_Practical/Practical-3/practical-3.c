#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    printf("Before fork()\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("\n--- Child Process ---\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());
        printf("State: Running\n");

        sleep(10);

        printf("Child process terminating...\n");
        exit(0);
    }
    else
    {
        printf("\n--- Parent Process ---\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());
        printf("Child PID: %d\n", pid);
        printf("State: Running\n");

        wait(NULL);

        printf("Child terminated.\n");
        printf("Parent process terminating...\n");
    }

    return 0;
}
