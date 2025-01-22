#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define UJASHO 1
#define ALPHABET_SIZE 26

typedef struct trieNode{
  struct trieNode *child[ALPHABET_SIZE];
  int is_end;
} trieNode;

trieNode *createNode(){
  trieNode *node = (trieNode *)malloc(sizeof(trieNode));
	for (int i = 0; i < ALPHABET_SIZE; i++){
          node->child[i] = NULL;
	}
        node->is_end = 0;
        return node;
}

int insert(trieNode *root, char const *word){
  if (root == NULL){
    return UJASHO;
  }

  trieNode *current = root;
  while(*word){
	int index = *word - 'a';
    if(current->child[index] == NULL){
      // создадим узел если его нету
      current->child[index] = createNode();
    }
    current = current->child[index]; // переход к некст узлу
    word++;
  }
  current->is_end = 1; // помечаем конец слова
}

int search(trieNode *root, char const *word){
  if (root == NULL){
    return UJASHO;
  }

  trieNode *current = root;
  while(*word){
	int index = *word - 'a';
        if(!current->child[index]){
			return OK; // Если узел отсутствует - строка отсутствует
        }
        current = current->child[index];
        word++;
  }
  return current->is_end;
}

int startsWith(trieNode *root, char const *prefix){
  if (root == NULL){
    return UJASHO;
  }

  trieNode *current = root;
  while(*prefix){
    int index = *prefix - 'a';
      if(!current->child[index]){
		  return OK; // Если узел отсутствует - строка отсутствует
        }
        current = current->child[index];
        prefix++;
  }
  return UJASHO;
}

void freeNode(trieNode *root){
	if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++){
      freeNode(root->child[i]);
    }
    free(root);
}

int main(){

}
