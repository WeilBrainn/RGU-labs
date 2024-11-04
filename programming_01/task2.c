#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// функция для подсчёта длины строки
int calculating_length(char *str)
{
  // инициализация длинны строки
  int length = 0;

  // Проходимся по строке
  while (str[length] != '\0')
  {
    length++;
  }
  // возвращаем значение длинны строки
  return length;
}

char *reverse_string(char *str)
{
  int length = calculating_length(str); // Определяем длину строки

  // Выделяем память для реверсированной строки
  char *reversed = (char *)malloc((length + 1) * sizeof(char));
  if (reversed == NULL)
  {
    printf("Ошибка выделения памяти\n");
    exit(1);
  }

  // Копируем символы в обратном порядке
  for (int i = 0; i < length; i++)
  {
    reversed[i] = str[length - i - 1];
  }
  reversed[length] = '\0'; // Устанавливаем нуль-терминатор

  return reversed; // Возвращаем указатель на реверсированную строку
}

// функция преобразование нечётных символов в верхний регистр
char *uppercase_odd_positions(const char *str)
{
  // вызываем функицю нахождения длинны строки
  int lenght = calculating_length(str);
  // выделяем память для строки с верхним рег.
  char *upper_string = (char *)malloc((lenght + 1) * sizeof(char));
  // проверка на выделение памяти
  if (upper_string == NULL)
  {
    printf("Братанчик, у тебя ошибка выделения памяти =))");
    exit(1);
  }

  // перебор символов и преобразование
  for (int i = 0; i < lenght; i++)
  {
    if (i % 2 != 0)
    {
      upper_string[i] = toupper(str[i]);
    }
    else
    {
      upper_string[i] = str[i];
    }
  }

  // ставим в конце нуль
  upper_string[lenght] = '\0';

  // возвращаем измененной строки
  return upper_string;
}

// функция сортировки цифр/символов
char *sort_string(const char *str)
{
  // получаем длину текста
  int lenght = calculating_length(str);
  // Массивы для хранения цифр, букв и других символов
  char *numbers = malloc(lenght + 1);
  char *letters = malloc(lenght + 1);
  char *other_symbols = malloc(lenght + 1);
  // Индексы для записи в соответствующие массивы
  int num_index = 0;
  int letter_index = 0;
  int other_index = 0;
  // новая строка и индекс к ней
  char *new_str = malloc(lenght + 1);
  int new_str_index = 0;

  for (int i = 0; i < lenght; i++)
  {
    // проверка на то строка это или нет
    if (isdigit(str[i])) // Если цифра
    {
      numbers[num_index++] = str[i];
    }
    else if (isalpha(str[i])) // Если буква
    {
      letters[letter_index++] = str[i];
    }
    else // Остальные символы
    {
      other_symbols[other_index++] = str[i];
    }
  }

  // добавляем в новую строку - цифры
  for (int j = 0; j < num_index; j++, new_str_index++)
  {
    new_str[new_str_index] = numbers[j];
  }

  // добавляем в новую строку - буквы
  for (int k = 0; k < letter_index; k++, new_str_index++)
  {
    new_str[new_str_index] = letters[k];
  }

  // добавляем в новую стоку - символы
  for (int h = 0; h < other_index; h++, new_str_index++)
  {
    new_str[new_str_index] = other_symbols[h];
  }

  // ставим нуль-терминатор
  new_str[new_str_index] = '\0';
  // принтуем что получилось (нужно будет удалить)
  printf("%s\n", new_str);

  // возвращаем новую строку
  return new_str;
}

char *concatenation_string(char *strings[], int count_string, unsigned int seed)
{
  srand(seed); // Инициализация генератора случайных чисел

  // Подсчёт общей длины всех строк с пробелами
  int total_length = 0;
  for (int i = 1; i < count_string; i += 2)
  {
    int j = 0;
    while (strings[i][j] != '\0')
    {
      total_length++;
      j++;
    }
    total_length++; // Добавляем 1 к длине для пробела
  }
  total_length -= 1; // Убираем лишний пробел в конце

  // Выделение памяти для новой строки
  char *new_str = (char *)malloc((total_length + 1) * sizeof(char));
  if (new_str == NULL)
  {
    printf("Ошибка выделения памяти\n");
    exit(1);
  }

  // Создаём массив индексов для чётных строк
  int even_count = (count_string + 1) / 2;
  int indices[even_count];
  for (int i = 0, j = 1; i < even_count; i++, j += 2)
  {
    indices[i] = j;
  }

  // Перемешивание массива индексов
  for (int i = 0; i < even_count; i++)
  {
    int random_index = rand() % even_count;
    int temp = indices[i];
    indices[i] = indices[random_index];
    indices[random_index] = temp;
  }

  // Конкатенация строк по случайным индексам
  char *current = new_str;
  for (int i = 0; i < even_count; i++)
  {
    int idx = indices[i];
    int j = 0;
    while (strings[idx][j] != '\0')
    {
      *current = strings[idx][j];
      current++;
      j++;
    }
    if (i < even_count - 1)
    { // Добавляем пробел после каждой строки, кроме последней
      *current = ' ';
      current++;
    }
  }

  *current = '\0'; // Устанавливаем нуль-терминатор
  return new_str;  // Возвращаем указатель на новую строку
}

// функция для сравнивания строк (стринг.h в банане)
int compare_strings(const char *str1, const char *str2)
{
  int i = 0;
  // прогоняем по символам двух строк до конца одной из них
  while (str1[i] != '\0' && str2[i] != '\0')
  {
    if (str1[i] != str2[i]) // если символы не совпадают
    {
      return str1[i] - str2[i]; // вернем разницу символов
    }
    i++; // переход к некст символу
  }
  // возвращаем разницу, если одна строка короче другой
  return str1[i] - str2[i];
}

int main(int argc, char *argv[])
{
  // Проверяем, что передано достаточно аргументов (минимум 3)
  if (argc < 3)
  {
    printf("Использование: %s <flag> [дополнительные аргументы]\n", argv[0]);
    return 1; // вернем ошибочку
  }

  // проверка на флаг -l (подсчет длинны строки)
  if (compare_strings(argv[1], "-l") == 0)
  {
    if (argc < 3) // Проверка на наличие строки для подсчёта длины
    {
      printf("Для флага -l требуется строка! \n");
      return 1;
    }
    int lenght = calculating_length(argv[2]);
    printf("Длина строки: %d\n", lenght);
  }

  // проверка флага -r (переворот строки)
  else if (compare_strings(argv[1], "-r") == 0)
  {
    if (argc < 3) // Проверка на наличие строки для подсчёта длины
    {
      printf("Для флага -r требуется строка! \n");
      return 1;
    }
    char *reversed = reverse_string(argv[2]);      // що тут говорить, вызываем функцию реверса
    printf("Перевернутая строка: %s\n", reversed); // принтуем результат
    free(reversed);                                // освобождаем память
  }
  // Проверка на флаг -u (верхний регистр нечётных символов)
  else if (compare_strings(argv[1], "-u") == 0)
  {
    if (argc < 3)
    {
      printf("Для флага -u требуется строка! \n");
      return 1;
    }
    char *uppercase_str = uppercase_odd_positions(argv[2]); // вызываем функцию аппер-кейса
    printf("Строка с нечетными символами в верхнем регистре: %s\n", uppercase_str);
    free(uppercase_str); // освобождаем память - или бан.
  }
  // Проверка на флаг -c (конкатенация строк в случайном порядке)
  else if (compare_strings(argv[1], "-c") == 0)
  {
    if (argc > 4) // а вот туть должна быть seed и хотя бы одна строка
    {
      printf("Для флага -c требуется seed и хотя бы одна строка\n");
      return 1;
    }
    unsigned int seed = (unsigned int)atoi(argv[2]); // преобразуем строку seed в число
    // вызываем функцию начиная с 3 и до конца агрументов
    char *concatenated_str = concatenation_string(argv + 3, argc - 3, seed);
    printf("Конкатенированная строка: %s\n", concatenated_str); // Выводим результат
    free(concatenated_str);                                     // Освобождаем память
  }
  // если не один флаг не совпал, то желаем удачи
  else
  {
    printf("Неизвестный флаг: %s\n", argv[1]);
    printf("Все-го хо-ро-ше-го!!! \n");
    return 1;
  }

  // успешное завершение программы
  return 0;
}