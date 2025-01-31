#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_KEYWORDS 10
#define MAX_LEN 256

// List of C keywords
const char *keywords[MAX_KEYWORDS] = {
    "int", "float", "char", "if", "else", "return", "while", "for", "void", "double"
};

// Function to check if a string is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    char operators[] = "+-*/=<>!&|";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

void lexicalAnalysis(FILE *file) {
    char ch, buffer[MAX_LEN];
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        // Skip whitespaces
        if (isspace(ch)) {
            if (index > 0) {
                buffer[index] = '\0';
                if (isKeyword(buffer))
                    printf("Keyword: %s\n", buffer);
                else
                    printf("Identifier: %s\n", buffer);
                index = 0;
            }
            continue;
        }

        // If character is an operator
        if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
            continue;
        }

        // If character is a letter or digit (part of an identifier or keyword)
        if (isalnum(ch) || ch == '_') {
            buffer[index++] = ch;
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                if (isKeyword(buffer))
                    printf("Keyword: %s\n", buffer);
                else
                    printf("Identifier: %s\n", buffer);
                index = 0;
            }
        }
    }

    // Handle last token in file
    if (index > 0) {
        buffer[index] = '\0';
        if (isKeyword(buffer))
            printf("Keyword: %s\n", buffer);
        else
            printf("Identifier: %s\n", buffer);
    }
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Lexical Analysis Output:\n");
    lexicalAnalysis(file);

    fclose(file);
    return 0;
}