#include "../include/lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer* init_lexer(const char* input) {
  Lexer* lexer = malloc(sizeof(Lexer));

  lexer->position = 0;
  lexer->input = input;
  lexer->size = strlen(input);
  lexer->current_char = input[lexer->position];

  return lexer;
}

void advance_lexer(Lexer *lexer) {
  lexer->position++;

  if (lexer->position >= lexer->size) {
    lexer->current_char = '\0';
  } else {
    lexer->current_char = lexer->input[lexer->position];
  }
}

// Function to initialise a token.
Token* init_token(const TType t, const char* value) {
  // Allocating memory for a new token.
  Token* token = malloc(sizeof(Token));
  token->type = t;
  token->value = malloc(strlen(value) + 1);

  if (token->value == NULL) {
    printf("Lexer: Failed to allocate memory for token value.\n");
    free(token);
    exit(1);
  }

  strcpy(token->value, value);

  // Return the pointer that references the newly initialised token.
  return token;
}

Token* next_token(Lexer* lexer) {
  while (lexer->current_char != '\0') {
    switch (lexer->current_char) {
      case ' ':
        advance_lexer(lexer);
        break;

      case '+':
        advance_lexer(lexer);
        return init_token(T_OPERATOR, "+");

      case '-':
        advance_lexer(lexer);
        return init_token(T_OPERATOR, "-");

      case '*':
        advance_lexer(lexer);
        return init_token(T_OPERATOR, "*");

      case '/':
        advance_lexer(lexer);
        return init_token(T_OPERATOR, "/");

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        return build_number(lexer);

      default:
        printf("Lexer error: Encountered unexpected token, got '%c'", lexer->current_char);
        exit(1);
    }
  }

  return init_token(T_EOF, "\0");
}

Token* build_number(Lexer* lexer) {
  size_t len = 0;
  size_t capacity = 16;

  bool is_float = false;
  char* number_string = malloc(capacity * sizeof(char));
  number_string[0] = lexer->current_char;

  advance_lexer(lexer);

  while (lexer->current_char >= '0' && lexer->current_char <= '9' || lexer->current_char == '.')  {
    if (lexer->current_char == '.') {
      if (is_float) {
        printf("Lexer error: A number must not contain more than one .");
        exit(1);
      }

      is_float = true;
    }
    len++;
    if (len >= capacity) {
      capacity += 10;
      number_string = realloc(number_string, capacity * sizeof(char));

      if (!number_string) {
        fprintf(stderr, "Lexer error: Memory allocation failed at build_number.\n");
      }
    }

    number_string[len] = lexer->current_char;
    advance_lexer(lexer);
  }

  if (is_float) {
    Token* token = init_token(T_FLOAT, number_string);
    free(number_string);
    return token;
  } else {
    Token* token = init_token(T_INTEGER, number_string);
    free(number_string);
    return token;
  }
}