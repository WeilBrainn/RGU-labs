#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void release_resources(...)
{
  va_list args;         // переменная для работы с переменными аргументами
  va_start(args, args); // Инициализируем args для доступа к переменным аргументам

  void *resourse;  // указатель на ресурс или память
  int action_flag; // флаг определяющий действие для ресурса (например, 1 - освободить память, 2 - закрыть файл)

  // Цикл, который обрабатывает каждую пару аргументов (указатель и флаг действия)
  while (1)
  {
    resourse = (args, void *); // Получаем следующий аргумент из args как указатель на ресурс
    if (resourse == NULL)      // проверяем на NULL
    {
      break;
    }

    action_flag = va_arg(args, int); // получаем некст аргумент типа int

    if (action_flag == 1)
    {
      free(resourse); // если флаг 1 то освобождаем память
      printf("Сударь ваша память свободна. \n")
    }
    else if (action_flag == 2)
    {
      fclose((FILE *)resourse); // если флаг 2 то закрываем файл
      printf("Файл закрыт.\n");
    }
  }
  va_end(args); // Завершаем работу с переменными аргументами
}

int main()
{
  // К примеру откроем два файла
  FILE *file1 = fopen("name_file1.txt", "w");
  FILE *file2 = fopen("name_file2.txt", "w");

  // Выделим динамическую память
  int *buffer1 = ((int *)malloc(10 * sizeof(int)));
  int *buffer2 = ((int *)malloc(10 * sizeof(int)));

  // Вызов функции release_resources для освобождения всех ресурсов
  // Передаём ресурс и флаг действия для каждого, завершая список NULL
  release_resources(
      buffer1, 1, // Освободить память, выделенную для buffer1
      file1, 2,   // Закрыть файл file1
      buffer2, 1, // Освободить память, выделенную для buffer2
      file2, 2,   // Закрыть файл file2
      NULL        // Завершаем список аргументов NULL
  );

  return 0;
}