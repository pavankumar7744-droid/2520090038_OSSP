#include <stdio.h>
#include <string.h>

#define MAX 500

void parseEscapes(char *input) {
    char output[MAX];
    int i = 0, j = 0;

    while (input[i] != '\0') {

        if (input[i] == '\\') {
            i++;

            if (input[i] == '\0') {
                printf("Error: Incomplete escape sequence\n");
                return;
            }

            switch (input[i]) {
                case ' ':
                    output[j++] = ' ';
                    break;

                case '\\':
                    output[j++] = '\\';
                    break;

                case '|':
                    output[j++] = '|';
                    break;

                case '$':
                    output[j++] = '$';
                    break;

                case '&':
                    output[j++] = '&';
                    break;

                case ';':
                    output[j++] = ';';
                    break;

                case '>':
                    output[j++] = '>';
                    break;

                case '<':
                    output[j++] = '<';
                    break;

                case '"':
                    output[j++] = '"';
                    break;

                case '\'':
                    output[j++] = '\'';
                    break;

                default:
                    printf("Error: Unknown escape sequence \\%c\n",
                           input[i]);
                    return;
            }

            i++;
        }
        else {
            output[j++] = input[i++];
        }
    }

    output[j] = '\0';

    printf("\nOriginal : %s\n", input);
    printf("Parsed   : %s\n", output);
}

int main() {
    char input[MAX];

    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Error: Empty input\n");
        return 1;
    }

    parseEscapes(input);

    return 0;
}
