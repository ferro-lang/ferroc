#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"

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

  for (int i = 0; i < file_size; i++) {
    next_token(lexer);
  }

  // Clean up the memory.
  free(source_code);

  // The statement below indicates that the program has executed without errors.
  return 0;
}