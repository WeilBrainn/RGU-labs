#include "format_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define UJASHO 1

// преобразование числа в римские цифры
size_t print_roman(int num, FILE *stream, char *str)
{
  // символы римских цифр упорядочены по убыванию их значений
  // M = 1000, CM = 900 и т.п
  const char *romans[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

  char buffer[128] = {0};
  size_t pos = 0;
  int i = 0;

  while (num > 0)
    {
    if(num >= values[i])
      {
       strcat(buffer, romans[i]);
       pos += strlen(romans[i]);
       num -= values[i];
      }
      else
      {
        i++;
      }
    }

  if (stream) fputs(buffer, stream);
  if (str) strcpy(str, buffer);
  return pos;
}

// Преобразование числа в Цекендорфово представление
size_t print_zeckendorf(unsigned int num, FILE *stream, char *str)
{
  // Для хранения чисел Фибоначчи
  unsigned int fib[32] = {1, 2};
  int count = 2;

  while (fib[count - 1] + fib[count - 2] <= num) {
    fib[count] = fib[count - 1] + fib[count - 2];
    count++;
  }

  char buffer[128] = {0};
  size_t pos = 0;
  for (int i = count - 1; i >= 0; i--) {
    if (num >= fib[i]) {
      buffer[pos++] = '1';
      num -= fib[i];
    } else {
      buffer[pos++] = '0';
    }
  }
  buffer[pos++] = '1'; // конечная единица

  if (stream) fputs(buffer, stream);
  if (str) strcpy(str, buffer);
  return pos;
}

// конвертация в байты
size_t convert_to_base(int num, int base, int uppercase, FILE *stream, char *str)
{
    if (base < 2 || base > 36)
    {
        return UJASHO;
    }

    char buffer[1000];
    int index_buffer = 0;
    int temporary_count = num;
    char symbol;

    while (temporary_count != 0)
    {
        // вычисляем остаток
        int result = temporary_count % base;

        // преобразуем результат в символ
        if (result < 10)
        {
            symbol = result + '0';
        }
        else
        {
            symbol = (result - 10) + (uppercase ? 'A' : 'a');
        }

        // сохраняем символ в буфер
        buffer[index_buffer++] = symbol;

        temporary_count /= base;
    }

    // если требуется, записываем результат в поток или строку
    if (stream != NULL)
    {
        for (int i = index_buffer - 1; i >= 0; i--)
        {
            fputc(buffer[i], stream);
        }
    }

    if (str != NULL)
    {
        for (int i = 0; i < index_buffer; i++)
        {
            str[i] = buffer[index_buffer - i - 1];
        }
        str[index_buffer] = '\0'; // добавляем завершающий ноль
    }

    return index_buffer;
}

// преобразуем в десятичную степень
size_t convert_to_decimal(const char *num_str, int base, int uppercase, FILE *stream, char *str)
{

}

size_t memory_dump(void *data, char type, FILE *stream, char *str)
{

}