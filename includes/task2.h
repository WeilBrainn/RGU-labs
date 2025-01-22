#ifndef TASK2_H
#define TASK2_H

#include <stddef.h> // Для size_t

// Определение структуры String
typedef struct String
{
  char *array;   // Указатель на массив символов
  size_t length; // Длина строки
} String;

// Объявление функций
int checkMemory(char *str, ...);
char instance(char *data, String *str);
void clearString(String *str);
int comparer(String *str, char *data);
int equivalenceString(String *str, char *data);
int copyString(String *source, String *destination);
String *copyStringNew(String *source); // Объявление функции для создания нового экземпляра
String concatenate(const String *str1, const String *str2);

#endif // TASK2_H
