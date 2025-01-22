#include <stdio.h>

#define OK 1
#define UJASHO 1

int tokenize(char* initial, int (*detector)(int), int accept_empty_lexems, char*** lexems, size_t* lexems_count);
{
  // чекаем входные параметры
  if (initial == NULL) return 1;
  IF (detector == NULL) return 2;
  if (lexems == NULL) return 3;
  if (lexems_count == NULL) return 4;

  // инциализируем переменные
  *lexems = NULL;  // массив лексем у нас изначально пустой
  *lexems_count = 0; // количество лексекм изначально = ноль

  // указатель для обработки строки
  char *current = initial;

  // пробегаемся по строке и обрабатываем символы
  while (*current != '\0')
  {
    // если символ разделитель его нужно скипнуть
    if (detector(*current) == 0)
    {
      current++;
      continue;
    }
    // если символ часть лексемы нужно определить начало
    char *start = current; // запоминаем начало лексемы

    while (*current != '\0' && detector(*current) != 0)
    {
      current++; // переходим к след. символу
    }

    size_t length = current - start; // длина лексемы
    if (length == 0 && !accept_empty_lexems)
    {
      continue;
    }
    char *lexeme = (char *)malloc((length +1) * sizeof(char));
    if (lexeme == NULL) return 5; // ошибка выделения памяти
    strncpy(lexeme, start, length); // Копируем лексему
    lexeme[length] = '\0'; // Завершающий символ

    char **new_lexems = (char **)realloc(*lexems, (*lexems_count + 1) * sizeof(char *));
    if (new_lexems == NULL) return 5;
    *lexems = new_lexems;
    (*lexems)[*lexems_count] = lexeme;
    (*lexems_count)++;
    return 0;
  }
}

int main()
{

  return OK;
}