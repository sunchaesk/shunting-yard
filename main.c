
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TOKEN_LEN 100

// TODO:
// 1. change the lexer so that it identifies the values and stuff


typedef enum{
NUMBER,
STRING,
OP_PLUS,
OP_DIV,
OP_MULT,
OP_MINUS
} TokenType;

typedef struct {
    TokenType type;
    union{
        char value[MAX_TOKEN_LEN];
        char val;
    };
} Token;

typedef struct {
    Token * tokens;
    size_t len;
} Lexer;

///////////////////////////////////////////////////////
/// stack DS
///////////////////////////////////////////////////////
#define MAX_STACK_DEPTH 200

enum {ASSOC_NONE = 0, ASSOC_LEFT, ASSOC_RIGHT};

struct operator {
    char* op;
    int prec;
    int assoc;
    int unary;
} operators[] = {
{"+", 5, ASSOC_LEFT, 0},
{"-", 5, ASSOC_LEFT, 0},
{"*", 6, ASSOC_LEFT, 0},
{"/", 6, ASSOC_LEFT, 0}
};

struct operator* opstack[MAX_STACK_DEPTH];
int opstack_idx = -1;
float numstack[MAX_STACK_DEPTH];
int numstack_idx = -1;

void push_opstack(struct operator *op){
    if (opstack_idx > MAX_STACK_DEPTH - 1){
        fprintf(stderr, "ERROR: OP stack overflow\n");
        exit(1);
    } else {
        opstack[opstack_idx++] = op;
    }
}

void push_numstack(float num){
    if (numstack_idx > MAX_STACK_DEPTH - 1){
        fprintf(stderr, "ERROR: numstack overflow\n");
        exit(1);
    } else{
        numstack[numstack_idx++] = num;
    }
}

bool isempty_opstack(){
    if (opstack_idx == -1){
        return true;
    } else {
        return false;
    }
}

bool isempty_numstack(){
    if (numstack_idx == -1){
        return true;
    } else {
        return false;
    }
}

bool isfull_opstack(){
    if (opstack_idx == MAX_STACK_DEPTH - 1){
        return true;
    } else{
        return false;
    }
}

bool isfull_numstack(){
    if (numstack_idx == MAX_STACK_DEPTH - 1){
        return true;
    } else {
        return false;
    }
}

struct operator * pop_opstack(){
    if (opstack_idx == -1){
        fprintf(stderr, "ERROR: op stack is empty\n");
        exit(1);
    }
    return opstack[--opstack_idx];
}

float pop_numstack(){
    if (numstack_idx == -1){
        fprintf(stderr, "ERROR: num stack is empty\n");
        exit(1);
    } else {
        return numstack[--numstack_idx];
    }
}

////////////////////////////////////////////////////////
/// debugging functions
////////////////////////////////////////////////////////

void d_lex(Lexer lex){
    for (int i = 0; (size_t)i < lex.len; i++){
        /* printf("Token: %d, value: %s\n", lex.tokens[i].type, lex.tokens[i].value); */
        if (lex.tokens[i].type == NUMBER || lex.tokens[i].type == STRING){
            printf("Token %d, value: %s\n", lex.tokens[i].type, lex.tokens[i].value);
        } else {
            printf("Token %d, value: %s\n", lex.tokens[i].type, lex.tokens[i].val);
        }
    }
}
////////////////////////////////////////////////////////

// only changes the inputted string between a STRING or a NUMBER
Lexer lex(char *input){
    Lexer lexer;
    lexer.tokens = malloc(sizeof(Token) * strlen(input));
    int token_index = 0;
    int char_index = 0;
    char current_char = input[char_index];

    while (current_char != '\0'){

        /*     char_index++; */
        /*     current_char = input[char_index]; */
        if (isspace(current_char)){
            char_index++;
            current_char = input[char_index];
        }

        if (current_char == '+'){
            Token tok;
            tok.type = OP_PLUS;
            lexer.tokens[token_index] = tok;
            token_index++;
        }

        if (current_char == '-'){
            Token tok;
            tok.type = OP_MINUS;
            tok.val = '-';
            lexer.tokens[token_index] = tok;
            token_index++;
        }

        if (current_char == '*'){
            Token tok;
            tok.type = OP_MULT;
            tok.val = '*';
            lexer.tokens[token_index] = tok;
            token_index++;
        }

        if (current_char == '/'){
            Token tok;
            tok.type = OP_DIV;
            tok.val = '/';
            lexer.tokens[token_index] = tok;
            token_index++;
        }

        if (isdigit(current_char)){
            char value[MAX_TOKEN_LEN];
            unsigned short value_idx = 0;
            while (isdigit(current_char)){
                value[value_idx++] = current_char;
                current_char = input[++char_index];
            }
            Token tok;
            tok.type = NUMBER;
            strcpy(tok.value, value);
            lexer.tokens[token_index] = tok;
            token_index++;
            memset(value,0,sizeof(value));
        }

        if (isalpha(current_char)){
            char value[MAX_TOKEN_LEN];
            unsigned short value_idx = 0;
            while (isalpha(current_char)){
                printf("%c\n", current_char);
                value[value_idx++] = current_char;
                current_char = input[++char_index];
                //printf("%d\n", char_index);
            }
            Token tok;
            tok.type = STRING;
            strcpy(tok.value, value);
            printf("tok_value: %s // value: %s\n", tok.value, value);
            lexer.tokens[token_index] = tok;
            token_index++;
            memset(value,0,sizeof(value));
        }

        // skip characters while current_char is whitespace
        /* while (isspace(current_char)){ */
        /*     char_index++; */
        /*     current_char = input[char_index]; */
        /* } */
    }
    lexer.len = token_index;
    return lexer;
}

/* void shunting(Lexer lex){ */
/*     for (size_t i = 0; i < lex.len; i++){ */
/*         Token curr = lex.tokens[i]; */
/*         if (curr.type == NUMBER){ */
/*             push_numstack(atof(curr.value)); */
/*         } else if (curr.){ */

/*         } */
/*     } */
/* } */

int main(){
    char input[] = "+\0";
    Lexer ll = lex(input);
    //d_lex(ll);
    return 0;
}
