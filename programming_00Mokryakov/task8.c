#include <stdio.h>

int maxPowerOfTwo(int n)
{
  // Базовый случай: если число 0, возвращаем 0
  if (n == 0)
    return 0;

  // Проверка на четность
  if (n % 2 != 0)
    return 0;

  // Рекурсивно делим число на 2 и добавляем 1 к счетчику
  return 1 + maxPowerOfTwo(n / 2);
}

int main()
{
  int a;

  // Ввод числа от пользователя
  printf("Введите целое число: ");
  scanf("%d", &a);

  // Нахождение максимальной степени 2
  int result = maxPowerOfTwo(a);

  // Вывод результата
  printf("Максимальная степень 2, на которую делится %d: %d\n", a, result);

  return 0;
}
