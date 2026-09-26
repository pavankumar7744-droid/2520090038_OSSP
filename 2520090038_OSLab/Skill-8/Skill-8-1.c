#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

void expandVariables(char *input) {
    char output[MAX];
    int i = 0, j = 0;

    while (input[i] != '\0' && j < MAX - 1) {

        if (input[i] == '$') {

            i++;

            char variable[100];
            int k = 0;

            /* ${VARIABLE} syntax */
            if (input[i] == '{') {
                i++;

                while (input[i] != '\0' &&
                       input[i] != '}' &&
                       k < 99) {
                    variable[k++] = input[i++];
                }

                if (input[i] == '}')
                    i++;
            }

            /* $VARIABLE syntax */
            else {
                while ((isalnum(input[i]) || input[i] == '_') &&
                       k < 99) {
                    variable[k++] = input[i++];
                }
            }

            variable[k] = '\0';

            if (k == 0) {
                output[j++] = '$';
                continue;
            }

            char *value = getenv(variable);

            if (value != NULL) {
                for (int x = 0;
                     value[x] != '\0' && j < MAX - 1;
                     x++) {
                    output[j++] = value[x];
                }
            }
            else {
                printf("Warning: Undefined variable '%s'\n",
                       variable);
            }
        }

        else {
            output[j++] = input[i++];
        }
    }

    output[j] = '\0';

    printf("Expanded: %s\n", output);
}

int main() {
    char input[MAX];

    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Error: Empty input\n");
        return 1;
    }

    expandVariables(input);

    return 0;
}
