#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1000000

int main() {
    int *data = malloc(SIZE * sizeof(int));

    if (data == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < SIZE; i++)
        data[i] = 100;

    printf("Parent PID: %d\n", getpid());
    printf("Before fork: data[0] = %d\n", data[0]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        free(data);
        return 1;
    }

    if (pid == 0) {

        printf("\nChild PID: %d\n", getpid());
        printf("Before modification: data[0] = %d\n", data[0]);

        data[0] = 999;

        printf("After modification: data[0] = %d\n", data[0]);

        printf("Child memory address: %p\n", (void *)&data[0]);

        sleep(5);

        free(data);
        exit(0);
    }

    else {
        sleep(1);

        printf("\nParent PID: %d\n", getpid());
        printf("Parent data[0] = %d\n", data[0]);
        printf("Parent memory address: %p\n", (void *)&data[0]);

        wait(NULL);

        free(data);
    }

    return 0;
}
