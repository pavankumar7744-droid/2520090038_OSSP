#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal) {
    if (signal == SIGINT) {
        printf("\nSIGINT received: Ctrl+C pressed.\n");
    }
    else if (signal == SIGTERM) {
        printf("\nSIGTERM received: Termination requested.\n");
    }
    else if (signal == SIGUSR1) {
        printf("\nSIGUSR1 received: User-defined event occurred.\n");
    }
}

int main() {
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    printf("Process ID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1) {
        pause();
    }

    return 0;
}
