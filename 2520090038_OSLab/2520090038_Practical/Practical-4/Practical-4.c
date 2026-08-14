#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t child1, child2, child3;
    int status;

    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1: PID = %d\n", getpid());
        sleep(3);
        printf("Child 1 completed.\n");
        exit(10);
    }

    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2: PID = %d\n", getpid());
        sleep(1);
        printf("Child 2 completed.\n");
        exit(20);
    }

    child3 = fork();

    if (child3 == 0)
    {
        printf("Child 3: PID = %d\n", getpid());
        sleep(2);
        printf("Child 3 completed.\n");
        exit(30);
    }

    printf("Parent: PID = %d\n", getpid());

    printf("\nUsing wait():\n");

    pid_t finished = wait(&status);

    printf("wait() collected child PID: %d\n", finished);
    printf("Exit status: %d\n", WEXITSTATUS(status));

    printf("\nUsing waitpid() for Child 1:\n");

    waitpid(child1, &status, 0);

    printf("waitpid() collected Child 1 PID: %d\n", child1);
    printf("Exit status: %d\n", WEXITSTATUS(status));

    waitpid(child3, &status, 0);

    printf("waitpid() collected Child 3 PID: %d\n", child3);
    printf("Exit status: %d\n", WEXITSTATUS(status));

    return 0;
}-
