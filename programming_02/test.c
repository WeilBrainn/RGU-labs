
#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла дерева
struct Node
{
  int value;          // Значение узла
  struct Node *left;  // Указатель на левый дочерний узел
  struct Node *right; // Указатель на правый дочерний узел
};

// Функция для создания нового узла
struct Node *create_node(int value)
{
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node)); // Выделение памяти для нового узла
  new_node->value = value;                                            // Установка значения узла
  new_node->left = NULL;                                              // Инициализация указателя на левый узел
  new_node->right = NULL;                                             // Инициализация указателя на правый узел
  return new_node;                                                    // Возвращение указателя на новый узел
}

// Функция для вставки значения в бинарное дерево
struct Node *insert(struct Node *node, int value)
{
  // Если дерево пустое, возвращаем новый узел
  if (node == NULL)
  {
    return create_node(value);
  }

  // Иначе рекурсивно вставляем узел в правильное место
  if (value < node->value)
  {
    node->left = insert(node->left, value);
  }
  else
  {
    node->right = insert(node->right, value);
  }

  return node; // Возвращаем текущий узел
}

// Функция для обхода дерева в порядке возрастания
void in_order_traversal(struct Node *node)
{
  if (node != NULL)
  {
    in_order_traversal(node->left); // Сначала обходим левое поддерево
    printf("%d ", node->value);
    in_order_traversal(node->right); // И, наконец, обходим правое поддерево
  }
  printf("/");
}

// Главная функция
int main()
{
  struct Node *root = NULL; // Корень дерева

  printf(sizeof(char));

  // Вставка значений в дерево
  root = insert(root, 7);
  root = insert(root, 12);
  root = insert(root, 4);
  root = insert(root, 6);
  root = insert(root, 10);
  root = insert(root, 3);
  root = insert(root, 9);
  root = insert(root, 11);

  // Обход дерева
  printf("Обход дерева в порядке возрастания: ");
  in_order_traversal(root);
  printf("\n");

  return 0; // Завершение программы
}