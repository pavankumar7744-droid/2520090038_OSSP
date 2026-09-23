#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 10;
static int static_var = 20;

void code_function() {
    printf("Code   : %p\n", (void *)code_function);
}

int main() {
    int stack_var = 30;
    static int local_static = 40;
    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL) {
        perror("malloc");
        return 1;
    }

    *heap_var = 50;

    printf("PID: %d\n\n", getpid());

    printf("Memory Addresses:\n");
    printf("Code           : %p\n", (void *)code_function);
    printf("Global         : %p\n", (void *)&global_var);
    printf("Static         : %p\n", (void *)&static_var);
    printf("Local Static   : %p\n", (void *)&local_static);
    printf("Heap           : %p\n", (void *)heap_var);
    printf("Stack          : %p\n", (void *)&stack_var);

    printf("\nProcess is running. Press ENTER to exit...\n");
    getchar();

    free(heap_var);

    return 0;
}
