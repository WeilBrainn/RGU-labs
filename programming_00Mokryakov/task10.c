#include <stdio.h>

int main()
{
  unsigned int n;

  // Ввод 2^p разрядного целого числа
  printf("Введите 2^p разрядное целое число: ");
  scanf("%u", &n);

  // Выполнение поксора всех битов
  // Результат будет 1, если количество единиц нечетное, и 0, если четное
  int result = 0;

  // Проверяем каждый бит, если он равен 1, увеличиваем результат
  result ^= (n & 1);       // Проверяем 0-й бит
  result ^= (n >> 1 & 1);  // Проверяем 1-й бит
  result ^= (n >> 2 & 1);  // Проверяем 2-й бит
  result ^= (n >> 3 & 1);  // Проверяем 3-й бит
  result ^= (n >> 4 & 1);  // Проверяем 4-й бит
  result ^= (n >> 5 & 1);  // Проверяем 5-й бит
  result ^= (n >> 6 & 1);  // Проверяем 6-й бит
  result ^= (n >> 7 & 1);  // Проверяем 7-й бит
  result ^= (n >> 8 & 1);  // Проверяем 8-й бит
  result ^= (n >> 9 & 1);  // Проверяем 9-й бит
  result ^= (n >> 10 & 1); // Проверяем 10-й бит
  result ^= (n >> 11 & 1); // Проверяем 11-й бит
  result ^= (n >> 12 & 1); // Проверяем 12-й бит
  result ^= (n >> 13 & 1); // Проверяем 13-й бит
  result ^= (n >> 14 & 1); // Проверяем 14-й бит
  result ^= (n >> 15 & 1); // Проверяем 15-й бит
  result ^= (n >> 16 & 1); // Проверяем 16-й бит
  result ^= (n >> 17 & 1); // Проверяем 17-й бит
  result ^= (n >> 18 & 1); // Проверяем 18-й бит
  result ^= (n >> 19 & 1); // Проверяем 19-й бит
  result ^= (n >> 20 & 1); // Проверяем 20-й бит
  result ^= (n >> 21 & 1); // Проверяем 21-й бит
  result ^= (n >> 22 & 1); // Проверяем 22-й бит
  result ^= (n >> 23 & 1); // Проверяем 23-й бит
  result ^= (n >> 24 & 1); // Проверяем 24-й бит
  result ^= (n >> 25 & 1); // Проверяем 25-й бит
  result ^= (n >> 26 & 1); // Проверяем 26-й бит
  result ^= (n >> 27 & 1); // Проверяем 27-й бит
  result ^= (n >> 28 & 1); // Проверяем 28-й бит
  result ^= (n >> 29 & 1); // Проверяем 29-й бит
  result ^= (n >> 30 & 1); // Проверяем 30-й бит
  result ^= (n >> 31 & 1); // Проверяем 31-й бит

  // Вывод результата
  printf("Результат поксора всех битов: %d\n", result);

  return 0;
}