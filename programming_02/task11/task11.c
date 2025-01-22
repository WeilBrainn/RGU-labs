#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "command_parser.h"
#include "debugger.h"
#include "ash.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <script_file>\n", argv[0]);
    return 1;
  }

  // Загрузка файла
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  // Инициализация
  Token *tokens = lex(file);
  fclose(file);

  if (!tokens) {
    fprintf(stderr, "Lexer failed\n");
    return 1;
  }

  InstructionTree *tree = parse(tokens);
  if (!tree) {
    fprintf(stderr, "Parser failed\n");
    return 1;
  }

  // Выполнение инструкций
  if (!execute(tree)) {
    fprintf(stderr, "Execution failed\n");
    return 1;
  }

  free_tree(tree);
  free_tokens(tokens);
  return 0;
}
