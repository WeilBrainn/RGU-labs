#include <stdio.h>

int main()
{
  int a;

  // Ввод числа от пользователя
  printf("Введите число a: ");
  scanf("%d", &a);

  // Вычисление младшего бита
  int lsb = a & 1; // младший бит равен a AND 1

  // Вывод младшего бита
  printf("Младший бит числа %d: %d\n", a, lsb);

  return 0;
}