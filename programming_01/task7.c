#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

// Проверка числа на Капрекара в системе счисления с основанием base
int isKaprekar(int num, int base) {
  if (num == 0) return 0;

  int square = num * num;
  int digits = 0;
  int temp = square;

  // Подсчет количества цифр в квадрате
  while (temp > 0) {
    digits++;
    temp /= base;
  }

  int powBase = 1;
  for (int i = 1; i <= digits / 2; i++) {
    powBase *= base;
  }

  int left = square / powBase;
  int right = square % powBase;

  return (left + right == num);
}

// Функция с переменным числом аргументов
void findKaprekarNumbers(int base, int count, ...) {
  va_list args;
  va_start(args, count);

  printf("число в базе %d:\n", base);

  for (int i = 0; i < count; i++) {
    char *str = va_arg(args, char*);
    int num = strtol(str, NULL, base);

    if (isKaprekar(num, base)) {
      printf("%s (десятичный: %d)\n", str, num);
    }
  }

  va_end(args);
}

// Пример использования
int main() {
  findKaprekarNumbers(10, 5, "9", "45", "297", "1", "0");
  findKaprekarNumbers(2, 3, "1", "10", "11001");

  return 0;
}
