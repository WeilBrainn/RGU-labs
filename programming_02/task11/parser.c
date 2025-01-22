#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

InstructionTree *parse(Token *tokens) {
  InstructionTree *tree = malloc(sizeof(InstructionTree));
  tree->head = NULL;
  tree->tail = NULL;

  int i = 0;
  while (tokens[i].type != TOKEN_EOF) {
    InstructionNode *node = malloc(sizeof(InstructionNode));
    strcpy(node->command, tokens[i++].value);
    node->arg_count = 0;

    while (tokens[i].type == TOKEN_LITERAL || tokens[i].type == TOKEN_IDENTIFIER) {
      strcpy(node->args[node->arg_count++], tokens[i++].value);
    }

    node->next = NULL;
    if (!tree->head) {
      tree->head = node;
    } else {
      tree->tail->next = node;
    }
    tree->tail = node;
  }

  return tree;
}
