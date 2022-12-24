
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_TOKEN_LEN 100

////////////////////////////////////////////////////
////   Lexer
////////////////////////////////////////////////////

// Token Types
typedef enum {
INTEGER,
PLUS,
MINUS,
MUL,
DIV,
LPAREN,
RPAREN,
} TokenType;

typedef struct Token {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;

void d_print_token(Token tok){
    printf("Type: %d, Value: %s\n", tok.type, tok.value);
}
// Token Type ends

// Lexer
typedef struct {
    size_t idx;
    char current_char;

} Lexer;

int main() {

}
