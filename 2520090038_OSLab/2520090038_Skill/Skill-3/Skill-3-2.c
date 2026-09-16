#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void addNode(Node **head, int value) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void displayList(Node *head) {
    printf("Linked List: ");

    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

void freeList(Node *head) {
    Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int capacity = 5;
    int size = 0;
    int *buffer = malloc(capacity * sizeof(int));

    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter numbers (-1 to stop):\n");

    while (1) {
        int value;
        scanf("%d", &value);

        if (value == -1)
            break;

        if (size == capacity) {
            capacity *= 2;

            int *temp = realloc(buffer, capacity * sizeof(int));

            if (temp == NULL) {
                free(buffer);
                printf("Reallocation failed\n");
                return 1;
            }

            buffer = temp;

            printf("Buffer resized to %d elements\n", capacity);
        }

        buffer[size++] = value;
    }

    printf("\nDynamic Array: ");

    for (int i = 0; i < size; i++)
        printf("%d ", buffer[i]);

    printf("\n");

    Node *head = NULL;

    for (int i = 0; i < size; i++)
        addNode(&head, buffer[i]);

    displayList(head);

    freeList(head);
    free(buffer);

    printf("Memory released successfully.\n");

    return 0;
}
