#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void release_resources(void *first, ...)
{
  va_list args;          // переменная для работы с переменными аргументами
  va_start(args, first); // Инициализируем args для доступа к переменным аргументам

  void *resource = first; // Начинаем с первого аргумента
  int action_flag;

  while (resource != NULL)
  {
    action_flag = va_arg(args, int);

    if (action_flag == 1)
    {
      free(resource); // если флаг 1 то освобождаем память
      printf("Сударь ваша память свободна. \n");
    }
    else if (action_flag == 2)
    {
      fclose((FILE *)resource); // если флаг 2 то закрываем файл
      printf("Файл закрыт.\n");
    }

    resource = va_arg(args, void *); // Получаем следующий ресурс
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