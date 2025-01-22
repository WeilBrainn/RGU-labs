#include <stdio.h>

// Функция для перевода числа в систему счисления с основанием 2^r
void convertToBase2R(int num, int r)
{
  // Создаем маску для извлечения цифр
  int mask = (1 << r) - 1; // Маска будет иметь r единиц в двоичном представлении

  // Массив для хранения цифр результата
  int digits[32]; // 32 бита достаточно для int
  int count = 0;

  // Пока число не станет равным 0
  while (num)
  {
    // Извлекаем младшие r бит с помощью маски
    digits[count] = num & mask;
    // Сдвигаем число вправо на r позиций
    num = num >> r;
    count++;
  }

  // Выводим результат в обратном порядке
  printf("Результат: ");
  for (int i = count - 1; i >= 0; i--)
  {
    printf("%d", digits[i]);
  }
  printf("\n");
}

int main()
{
  int number, r;

  printf("Введите десятичное число: ");
  scanf("%d", &number);

  printf("Введите r (от 1 до 5): ");
  scanf("%d", &r);

  if (r < 1 || r > 5)
  {
    printf("r должно быть от 1 до 5\n");
    return 1;
  }

  convertToBase2R(number, r);
  return 0;
}
