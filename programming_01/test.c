#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode
{
  int data;
  struct StackNode *next;
} StackNode;

StackNode *createNode(int data)
{
  StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
  if (!newNode)
  {
    return 1;
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void push(StackNode **root, int data)
{
  StackNode *newNode = createNode(data);
  newNode->next = *root;
  *root = newNode;
}

int pop(StackNode **root)
{
  if (*root == NULL)
  {
    return -1;
  }
  StackNode *temp = *root;
  *root = (*root)->next;
  int popped = temp->data;
  free(temp);
  return popped;
}
