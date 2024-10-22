#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"
#include "../include/parser.h"

#include <stdio.h>

char* make_indent(const int indent_size) {
  char* indent = malloc(indent_size * sizeof(char));

  for (int i =  0; i < indent_size; i++) {
    indent[i] = ' ';
  }

  return indent;
}

// Helper function to print the AST in a readable format
void print_ast(const Node* node, const int indent_size, const char* delimiter) {
  // Asserting, whether node is valid
  if (node == NULL) {
    return;
  }

  switch (node->type) {
    case NODE_NUMBER: {
      printf("%s%s%s", make_indent(indent_size), node->token->value, delimiter);
      break;
    }

    case NODE_BINARY_OPERATION: {
      printf("BinaryOperation(\n");
      print_ast(node->lnode, indent_size + 1, ",\n");
      print_ast(node->rnode, indent_size + 1, "");
      printf("\n)\n");
    }

    default:
      printf("Formatter Error: Node beyond capabilities: %d!", node->type);
      exit(1);
  }
}

// Starting point for the compiler,
// the following function would be automatically called, when the program executes.
int main(const int argc, char** argv) {
  // Asserting that, the program has been called with required number of command line arguments.
  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  // Opening the source file in read mode.
  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error opening the file(%s)", argv[1]);
    return 1;
  }

  // Getting the length of the source file.
  fseek(file, 0, SEEK_END);
  const long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Read the file contents to a string.
  char *source_code = malloc(file_size + 1);
  fread(source_code, 1, file_size, file);
  source_code[file_size] = '\0';

  // Close the file.
  fclose(file);

  // Setting up the lexer.
  Lexer* lexer = init_lexer(source_code);
  Parser* parser = init_parser(lexer);

  const Node* root = parse(parser);
  print_ast(root, 1, "");


  // Clean up the memory.
  free(source_code);

  // The statement below indicates that the program has executed without errors.
  return 0;
}