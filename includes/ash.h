#ifndef ASH_H
#define ASH_H

#define MAX_VAR_NAME 64
#define MAX_COMMANDS 32

typedef struct {
  char name[MAX_VAR_NAME];
  int value;
} Variable;

typedef struct {
  char original[MAX_COMMANDS][MAX_VAR_NAME];
  char synonym[MAX_COMMANDS][MAX_VAR_NAME];
} CommandTable;

#endif
