#include <stdio.h>
#include <string.h>

#define OK 0
#define UJASHO 1

int arrayList(char *fileName[], int count, int mode)
{
  // открываем файлы и пробегаемся по ним
  for (int i = 0; i < count; i++)
  {
    // открытие файла
    FILE *file = fopen(fileName[i], "r");
    // проверка на NULL
    if (file == NULL)
    {
      return UJASHO;
    }

    // подсчет длинны строк
    if (mode == 1)
    {
      int line_count = 0;
      int ch;

      // пробегаемся и считаем длинну строк
      while ((ch = fgetc(file)) != EOF)
      {
        if (ch == '\n')
        {
          line_count++;
        }
      }
      printf("Количество строк в файле %s: %d\n", fileName[i], line_count);
    }
    // подсчет максимальной длинны строки
    else if (mode == 2)
    {
      int maxLength = 0;
      int currentLength = 0;
      int ch;
      while ((ch = fgetc(file)) != EOF)
      {
        if (ch == '\n')
        {
          if (currentLength > maxLength)
          {
            maxLength = currentLength;
          }
          currentLength = 0;
        }
        else
        {
          currentLength++;
        }
      }
      if (currentLength > maxLength)
      {
        maxLength = currentLength;
      }
      printf("Максимальная длина строки в файле %s: %d\n", fileName[i], maxLength);
    }
    // закрываем файл
    fclose(file);
  }
  return OK;
}

int main()
{
  char *fileName[] = {"test.txt"};
  int count = sizeof(fileName) / sizeof(fileName[0]);

  int mode = 2;
  arrayList(fileName, count, mode);

  return OK;
}