#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

typedef enum {
    IDENTIFIER, KEYWORD, NUMBER, OPERATOR, UNKNOWN, END_OF_FILE
} TokenType;

const char *keywords[] = { "int", "float", "return", "if", "else", "while" };
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
} Token;

int is_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

const char *source_code = "int d = 10;";
int pos = 0;

Token get_next_token() {
    Token token;
    int ch;
    int i = 0;

    while (isspace(source_code[pos])) pos++;
    ch = source_code[pos++];

    if (ch == '\0') {
        token.type = END_OF_FILE;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    if (isalpha(ch)) {
        token.lexeme[i++] = ch;
        while (isalnum(source_code[pos])) {
            token.lexeme[i++] = source_code[pos++];
        }
        token.lexeme[i] = '\0';

        if (is_keyword(token.lexeme)) {
            token.type = KEYWORD;
        } else {
            token.type = IDENTIFIER;
        }
    } else if (isdigit(ch)) {
        token.lexeme[i++] = ch;
        while (isdigit(source_code[pos])) {
            token.lexeme[i++] = source_code[pos++];
        }
        token.lexeme[i] = '\0';
        token.type = NUMBER;
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=') {
        token.lexeme[i++] = ch;
        token.lexeme[i] = '\0';
        token.type = OPERATOR;
    } else {
        token.lexeme[i++] = ch;
        token.lexeme[i] = '\0';
        token.type = UNKNOWN;
    }

    return token;
}

void print_token(Token token) {
    const char *type_str;
    switch (token.type) {
        case IDENTIFIER: type_str = "IDENTIFIER"; break;
        case KEYWORD: type_str = "KEYWORD"; break;
        case NUMBER: type_str = "NUMBER"; break;
        case OPERATOR: type_str = "OPERATOR"; break;
        case UNKNOWN: type_str = "UNKNOWN"; break;
        case END_OF_FILE: type_str = "END_OF_FILE"; break;
    }
    printf("<%s, %s>\n", type_str, token.lexeme);
}

int main() {
    printf("Scanning predefined input: \"%s\"\n", source_code);

    Token token;
    do {
        token = get_next_token();
        print_token(token);
    } while (token.type != END_OF_FILE);

    return 0;
}