#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

void parseInput(char *input) {
    char output[MAX];
    int i = 0, j = 0;
    int quote = 0;

    while (input[i] != '\0') {

        /* Single quotes: preserve everything literally */
        if (input[i] == '\'') {
            i++;
            while (input[i] != '\0' && input[i] != '\'') {
                output[j++] = input[i++];
            }

            if (input[i] == '\'')
                i++;

            continue;
        }

        /* Double quotes: preserve spaces, expand variables */
        if (input[i] == '"') {
            i++;

            while (input[i] != '\0' && input[i] != '"') {

                if (input[i] == '$') {
                    char variable[100];
                    int k = 0;

                    i++;

                    while ((input[i] >= 'A' && input[i] <= 'Z') ||
                           (input[i] >= 'a' && input[i] <= 'z') ||
                           (input[i] >= '0' && input[i] <= '9') ||
                           input[i] == '_') {

                        variable[k++] = input[i++];
                    }

                    variable[k] = '\0';

                    char *value = getenv(variable);

                    if (value != NULL) {
                        for (int x = 0; value[x] != '\0'; x++)
                            output[j++] = value[x];
                    }
                }
                else {
                    output[j++] = input[i++];
                }
            }

            if (input[i] == '"')
                i++;

            continue;
        }

        /* Variable expansion outside quotes */
        if (input[i] == '$') {
            char variable[100];
            int k = 0;

            i++;

            while ((input[i] >= 'A' && input[i] <= 'Z') ||
                   (input[i] >= 'a' && input[i] <= 'z') ||
                   (input[i] >= '0' && input[i] <= '9') ||
                   input[i] == '_') {

                variable[k++] = input[i++];
            }

            variable[k] = '\0';

            char *value = getenv(variable);

            if (value != NULL) {
                for (int x = 0; value[x] != '\0'; x++)
                    output[j++] = value[x];
            }

            continue;
        }

        output[j++] = input[i++];
    }

    output[j] = '\0';

    printf("\nParsed Output: %s\n", output);
}

int main() {
    char input[MAX];

    printf("Enter command/string: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Error: Empty input\n");
        return 1;
    }

    parseInput(input);

    return 0;
}
