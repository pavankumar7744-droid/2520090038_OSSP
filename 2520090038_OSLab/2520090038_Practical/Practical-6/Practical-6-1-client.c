#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define REQUEST_FIFO "request_fifo"
#define MAX_SIZE 256

int main() {
    char client_fifo[100];
    char message[MAX_SIZE];
    char response[MAX_SIZE];

    snprintf(client_fifo, sizeof(client_fifo),
             "client_fifo_%d", getpid());

    mkfifo(client_fifo, 0666);

    printf("Enter message: ");
    fgets(message, MAX_SIZE, stdin);

    message[strcspn(message, "\n")] = '\0';

    char request[MAX_SIZE + 100];

    snprintf(request, sizeof(request), "%s|%s",
         client_fifo, message);

    int request_fd = open(REQUEST_FIFO, O_WRONLY);

    if (request_fd == -1) {
        perror("open request FIFO");
        unlink(client_fifo);
        return 1;
    }

    write(request_fd, request, strlen(request) + 1);
    close(request_fd);

    int response_fd = open(client_fifo, O_RDONLY);

    if (response_fd == -1) {
        perror("open response FIFO");
        unlink(client_fifo);
        return 1;
    }

    memset(response, 0, MAX_SIZE);

    read(response_fd, response, MAX_SIZE - 1);

    printf("Server response: %s\n", response);

    close(response_fd);
    unlink(client_fifo);

    return 0;
}
