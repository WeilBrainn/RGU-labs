#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// функция получения длинны строки
int substring_lenght(char *str)
{
  int lenght = 0;

  while (str[lenght] != '\0')
  {
    lenght++;
  }

  return lenght;
}
// функция нахождения подстроки
int find_substring_in_files(char *substring, ...)
{
  va_list args;
  va_start(args, substring);

  while (1)
  {
    // получаем путь к файлу
    char *file_path = va_arg(args, char *);
    if (file_path == NULL)
      break;

    // открываем файлик
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
      printf("Не удалось открыть файл");
      break;
    }
    char line[1024];     // массив для чтения строк
    int line_number = 0; // счетчик для номера строки

    int sub_length = substring_lenght(substring); // получаем длинну строки

    // читаем файл пострчно
    while (fgets(line, sizeof(line), file) != NULL)
    {
      line_number++; // увеличиваем счетчик строк
      // проходим по каждому символу строки
      for (int i = 0; line[i] != '\0'; i++)
      {
        // проверка начинается ли подстрока или не-а
        if (line[i] == substring[0])
        {
          int j;
          // сравниваем каждый символ
          for (j = 0, j < sub_length && line[i + j] == substring[j]; j++)
          {
          }

          // если подстрока полностью совпала
          if (j == sub_length)
          {
            printf("Найдено в файле %s, строка %d, символ %d\n", file_path, line_number, i + 1);
          }
        }
      }
    }
    // не забываем закрыть файл или бан.
    fclose(file);
  }
  va_end(args); // завершаем работу с переменными аргументами
}

int main()
{
  find_substring_in_files("test", "file1.txt", "file2.txt", NULL);

  return 0;
}