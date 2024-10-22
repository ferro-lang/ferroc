#include "../include/parser.h";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Parser* init_parser(Lexer* lexer) {
  Parser* parser = malloc(sizeof(Parser));
  parser->lexer = lexer;
  parser->current_token = next_token(lexer);
  return parser;
}

void advance(Parser* parser, const TType t) {
  if (parser->current_token->type == t) {
    parser->current_token = next_token(parser->lexer);
  } else {
    printf("Parser error: Expected token to be %d but got %d", t, parser->current_token->type);
    exit(1);
  }
}

Node* factor(Parser* parser) {
  const Token* token = parser->current_token;

  if (token->type == T_INTEGER || token->type == T_FLOAT) {
    advance(parser, token->type);
    return init_number_node(token);
  } else {
    printf("Parser error: Encountered a token, beyond capabilities");
    exit(1);
  }
}

Node* init_binary_operation_node(Token* token, Node* lnode, Node* rnode) {
  Node* node = malloc(sizeof(Node));
  if (node == NULL) {
    printf("Parser error: Unable to assign memory for new node.");
    exit(1);
  }

  node->token = token;
  node->lnode = lnode;
  node->rnode = rnode;
  node->type = NODE_BINARY_OPERATION;

  return node;
}


Node* term(Parser* parser) {
  Node* node = factor(parser);

  while (
    parser->current_token->type == T_OPERATOR &&
    (strcmp(parser->current_token->value, "*") == 0 ||
      strcmp(parser->current_token->value, "/") == 0)
  ) {
    Token* token = parser->current_token;
    advance(parser, T_OPERATOR);

    node = init_binary_operation_node(token, node, factor(parser));
  }

  return node;
}

Node* expression(Parser* parser) {
  Node* node = term(parser);

  while (
    parser->current_token->type == T_OPERATOR &&
    (strcmp(parser->current_token->value, "+") == 0 ||
      strcmp(parser->current_token->value, "-") == 0)
  ) {
    Token* token = parser->current_token;
    advance(parser, T_OPERATOR);

    node = init_binary_operation_node(token, node, factor(parser));
  }

  return node;
}

Node* parse(Parser* parser) {
  return expression(parser);
}

Node* init_number_node(Token* token) {
  Node* node = malloc(sizeof(Node));

  if (node == NULL) {
    printf("Parser error: Unable to assign memory for new node.");
    exit(1);
  }

  node->lnode = NULL;
  node->rnode = NULL;
  node->token = token;
  node->type = NODE_NUMBER;

  return node;
}
