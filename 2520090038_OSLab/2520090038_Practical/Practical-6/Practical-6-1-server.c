#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define REQUEST_FIFO "request_fifo"
#define MAX_SIZE 256

int main() {
    char buffer[MAX_SIZE];
    char response[MAX_SIZE];

    mkfifo(REQUEST_FIFO, 0666);

    printf("Server started. Waiting for clients...\n");

    int fd = open(REQUEST_FIFO, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while (1) {
        memset(buffer, 0, MAX_SIZE);

        ssize_t n = read(fd, buffer, MAX_SIZE - 1);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        printf("Client message: %s\n", buffer);

        char *separator = strchr(buffer, '|');

        if (separator != NULL) {
            *separator = '\0';

            char *client_fifo = buffer;
            char *message = separator + 1;

            snprintf(response, MAX_SIZE,
                     "Server processed: %s", message);

            int response_fd = open(client_fifo, O_WRONLY);

            if (response_fd != -1) {
                write(response_fd, response, strlen(response) + 1);
                close(response_fd);
            }
        }
    }

    close(fd);
    unlink(REQUEST_FIFO);

    return 0;
}
