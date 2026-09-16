#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 50
#define MAX_LEN 100

typedef enum {
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    END
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_LEN];
} Token;

typedef struct Node {
    char command[MAX_LEN];
    struct Node *left;
    struct Node *right;
} Node;

Token tokens[MAX_TOKENS];
int token_count = 0;
int pos = 0;


void addToken(TokenType type, const char *value) {
    if (token_count >= MAX_TOKENS) {
        printf("Error: Too many tokens\n");
        exit(1);
    }

    tokens[token_count].type = type;
    strcpy(tokens[token_count].value, value);
    token_count++;
}

void tokenize(char *input) {
    int i = 0;

    while (input[i] != '\0') {

        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (input[i] == '|') {
            addToken(PIPE, "|");
            i++;
        }
        else if (input[i] == '<') {
            addToken(REDIRECT_IN, "<");
            i++;
        }
        else if (input[i] == '>') {
            addToken(REDIRECT_OUT, ">");
            i++;
        }
        else {
            char word[MAX_LEN];
            int j = 0;

            while (input[i] != '\0' &&
                   !isspace(input[i]) &&
                   input[i] != '|' &&
                   input[i] != '<' &&
                   input[i] != '>') {

                if (j < MAX_LEN - 1)
                    word[j++] = input[i];

                i++;
            }

            word[j] = '\0';

            if (j > 0)
                addToken(WORD, word);
        }
    }

    addToken(END, "END");
}


void printTokens() {
    printf("\nTokens:\n");

    for (int i = 0; i < token_count; i++) {

        if (tokens[i].type == WORD)
            printf("WORD          : %s\n", tokens[i].value);

        else if (tokens[i].type == PIPE)
            printf("PIPE          : |\n");

        else if (tokens[i].type == REDIRECT_IN)
            printf("REDIRECT_IN   : <\n");

        else if (tokens[i].type == REDIRECT_OUT)
            printf("REDIRECT_OUT  : >\n");

        else
            printf("END\n");
    }
}


Node *createNode(const char *command) {
    Node *node = malloc(sizeof(Node));

    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strcpy(node->command, command);
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node *parseCommand() {

    if (tokens[pos].type != WORD) {
        printf("Syntax Error: Expected command\n");
        return NULL;
    }

    Node *root = createNode(tokens[pos].value);
    pos++;

    while (tokens[pos].type == WORD) {

        Node *newNode = createNode(tokens[pos].value);
        root->right = newNode;
        pos++;
    }

    return root;
}

Node *parse() {

    if (tokens[0].type == END) {
        printf("Empty command\n");
        return NULL;
    }

    Node *left = parseCommand();

    if (left == NULL)
        return NULL;

    while (tokens[pos].type == PIPE) {

        pos++;

        if (tokens[pos].type != WORD) {
            printf("Syntax Error: Pipe requires a command after it\n");
            return NULL;
        }

        Node *right = parseCommand();

        if (right == NULL)
            return NULL;

        Node *pipeNode = createNode("|");

        pipeNode->left = left;
        pipeNode->right = right;

        left = pipeNode;
    }

    if (tokens[pos].type != END) {
        printf("Syntax Error near '%s'\n", tokens[pos].value);
        return NULL;
    }

    return left;
}


void printTree(Node *root, int level) {

    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("|-- %s\n", root->command);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}


void freeTree(Node *root) {

    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


int main() {

    char input[500];

    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    tokenize(input);

    printTokens();

    Node *tree = parse();

    if (tree != NULL) {
        printf("\nParse Tree:\n");
        printTree(tree, 0);

        printf("\nSyntax: VALID\n");
        printf("Execution structure generated successfully.\n");

        freeTree(tree);
    }
    else {
        printf("\nSyntax: INVALID\n");
    }

    return 0;
}
