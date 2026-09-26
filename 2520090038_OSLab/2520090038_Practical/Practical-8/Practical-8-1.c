#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    // malloc()
    int *a = malloc(5 * sizeof(int));

    if (a == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    for (i = 0; i < 5; i++)
        a[i] = i + 1;

    printf("malloc: ");
    for (i = 0; i < 5; i++)
        printf("%d ", a[i]);
    printf("\n");

    // calloc()
    int *b = calloc(5, sizeof(int));

    if (b == NULL) {
        free(a);
        return 1;
    }

    printf("calloc: ");
    for (i = 0; i < 5; i++)
        printf("%d ", b[i]);
    printf("\n");

    a = realloc(a, 10 * sizeof(int));

    if (a == NULL) {
        free(b);
        return 1;
    }

    for (i = 5; i < 10; i++)
        a[i] = i + 1;

    printf("realloc: ");
    for (i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");
    free(a);
    free(b);

    printf("Memory released successfully.\n");

    return 0;
}
