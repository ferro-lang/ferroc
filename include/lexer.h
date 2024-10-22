#ifndef LEXER_H
#define LEXER_H

typedef enum {
  T_EOF,
  T_FLOAT,
  T_INTEGER,
  T_OPERATOR,
} TType;

typedef struct {
  TType type;
  char* value;
} Token;

typedef struct {
  int position;
  unsigned long size;
  const char* input;
  char current_char;
} Lexer;

Lexer* init_lexer(const char* input);
void advance_lexer(Lexer* lexer);

Token* next_token(Lexer* lexer);
Token* init_token(TType t, char* value);
Token* build_number(Lexer* lexer);

#endif //LEXER_H
