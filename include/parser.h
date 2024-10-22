#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

typedef enum {
  NODE_NUMBER,
  NODE_BINARY_OPERATION
} NType;

typedef struct {
  NType type;
  Token* token;
  struct Node* lnode;
  struct Node* rnode;
} Node;

typedef struct {
  Lexer* lexer;
  Token* current_token;
} Parser;

Parser* init_parser(Lexer* lexer);
void advance(Parser* parser, TType t);

Node* term(Parser* parser);
Node* parse(Parser* parser);
Node* factor(Parser* parser);
Node* expression(Parser* parser);

Node* init_number_node(Token* token);
Node* init_binary_operation_node(Token* token, Node* lnode, Node* rnode);

#endif //PARSER_H
