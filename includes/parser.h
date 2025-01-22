#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct InstructionNode {
  char command[MAX_TOKEN_LEN];
  char args[MAX_TOKENS][MAX_TOKEN_LEN];
  int arg_count;
  struct InstructionNode *next;
} InstructionNode;

typedef struct {
  InstructionNode *head;
  InstructionNode *tail;
} InstructionTree;

InstructionTree *parse(Token *tokens);

#endif
