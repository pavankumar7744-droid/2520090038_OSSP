#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

void enableRawMode(struct termios *original)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

int main()
{
    struct termios original;
    char input[100];
    char ch;
    int index;

    enableRawMode(&original);

    while (1)
    {
        printf("\nmyshell> ");
        fflush(stdout);

        index = 0;

        while (1)
        {
            read(STDIN_FILENO, &ch, 1);

            if (ch == '\n' || ch == '\r')
            {
                input[index] = '\0';
                printf("\n");
                break;
            }

            if (ch == 127 || ch == 8)
            {
                if (index > 0)
                {
                    index--;
                    printf("\b \b");
                    fflush(stdout);
                }
                continue;
            }

            if (index < 99)
            {
                input[index] = ch;
                index++;

                printf("%c", ch);
                fflush(stdout);
            }
        }

        if (strcmp(input, "exit") == 0)
            break;

        printf("You entered: %s\n", input);
    }

    disableRawMode(&original);

    printf("Shell terminated.\n");

    return 0;
}
