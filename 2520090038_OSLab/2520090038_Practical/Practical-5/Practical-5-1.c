#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 100000

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent - Producer
        close(fd[0]);

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 1; i <= N; i++) {
            if (write(fd[1], &i, sizeof(i)) != sizeof(i)) {
                perror("write");
                break;
            }
        }

        close(fd[1]);

        wait(NULL);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("\nProducer generated %d items.\n", N);
        printf("Communication time: %.6f seconds\n", time_taken);
        printf("Throughput: %.2f items/second\n", N / time_taken);
    }
    else {
        // Child - Consumer
        close(fd[1]);

        int value;
        long count = 0;

        while (read(fd[0], &value, sizeof(value)) > 0) {
            count++;
        }

        close(fd[0]);

        printf("Consumer received %ld items.\n", count);
    }

    return 0;
}
