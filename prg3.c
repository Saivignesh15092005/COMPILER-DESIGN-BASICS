#include <stdio.h>
#include <string.h>
#include <ctype.h> // For isalpha, isdigit, etc.

// Function to check if a string is a keyword
int isKeyword(char *str) {
    char keywords[][10] = {"if", "else", "while", "for", "int", "float", "char", "return"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

// Function to check if a character is an operator
int isOperator(char c) {
    char operators[] = "+-*/%=<>!";
    for (int i = 0; i < strlen(operators); i++) {
        if (c == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch;
    char buffer[100]; // To store potential identifiers/keywords
    int i = 0;

    fp = fopen("input.c", "r"); // Assuming you have an input.c file
    if (fp == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isalpha(ch) || ch == '_') { // Potential identifier or keyword
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp); // Put the last character back
            i = 0;

            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
            memset(buffer, 0, sizeof(buffer)); // Clear buffer
        } else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        } else if (isdigit(ch)) {
            // Logic to identify numbers
            printf("Digit/Number: %c\n", ch);
            // You'll need to read subsequent digits to form a full number
        } else if (isspace(ch)) {
            // Ignore whitespace
        } else {
            // Handle other characters like parentheses, semicolons, etc.
            printf("Special character: %c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}

