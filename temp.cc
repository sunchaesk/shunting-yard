#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

#define MAX_OP_STACK 100
#define MAX_NUM_STACK 100

typedef enum {
NUMBER,
STRING
} TokenType;

typedef struct {
    TokenType token;
    char value[MAX_TOKEN_LEN];
} Token;

void lexer(char * input, Token * tokens, int * token_count){
    token_count = 0;
    int i  = 0;
    while (input[i] != '\0'){
        char curr = input[i];

        // parse digit
        if (isdigit(curr)){
            char value[MAX_TOKEN_LEN];
            int value_idx = 0;
            while (isdigit(curr)){
                value[value_idx++] = curr;
                curr = input[++i];
            }
            value[value_idx] = '\0';
            Token token;
            token.token = NUMBER;
            strcpy(token.value, value);
            tokens[(*token_count)++] = token;
        }
        else if (isalpha(curr)){
            char value[MAX_TOKEN_LEN];
            int value_idx = 0;
            while (isalpha(curr)){
                value[value_idx++] = curr;
                curr = input[++i];
            }
            value[value_idx] = '\0';
            Token token;
            token.token = STRING;
            strcpy(token.value, value);
            tokens[(*token_count)++] = token;
        }
        else {
            ++i;
        }
    }
}


int main() {
  char input[] = "hello 123 world 456";
  printf(input);
  Token tokens[MAX_TOKEN_LEN];
  int token_count;
  lexer(input, tokens, &token_count);

  for (int i = 0; i < token_count; ++i) {
    printf("Type: %d, Value: %s\n", tokens[i].token, tokens[i].value);
  }

  return 0;
}
