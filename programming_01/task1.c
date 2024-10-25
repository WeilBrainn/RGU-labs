#include <stdio.h>
#include <string.h>

void convert_to_base2r(unsigned int num, int r)
{
  // Маска для получения остатка при делении на 2^r
  unsigned int mask = (1 << r) - 1; // Например, если r = 2, то mask = 3 (11 в двоичной системе)
  char result[64];                  // Массив для хранения результата
  int index = 0;                    // Индекс для добавления символов в result

  // Пока num больше 0
  while (num > 0)
  {
    // Получаем остаток при делении с помощью побитовой операции И
    unsigned int remainder = num & mask;

    // Преобразуем остаток в символ и сохраняем его в result
    if (remainder < 10)
    {
      result[index++] = '0' + remainder; // Если остаток меньше 10, это цифра
    }
    else
    {
      result[index++] = 'A' + (remainder - 10); // Если остаток больше 10, это символ (A, B, C и т.д.)
    }

    // Сдвиг числа вправо на r бит для деления на 2^r
    num = num >> r;
  }

  // Добавляем нуль-терминатор в конец строки
  result[index] = '\0';

  // переворачием в обратном порядке
  for (int i = 0; i < index / 2; i++)
  {
    char temp = result[i];
    result[i] = result[index - i - 1];
    result[index - i - 1] = temp;
  }

  // Выводим результат
  printf("Результат в системе с основанием 2^%d: %s\n", r, result);
}

int main()
{
  unsigned int num;
  int r;

  // Ввод числа и основания
  printf("Введите число: ");
  scanf("%u", &num);

  printf("Введите значение r (1 <= r <= 5): ");
  scanf("%d", &r);

  // Проверка допустимого значения r
  if (r < 1 || r > 5)
  {
    printf("Недопустимое значение r. Оно должно быть от 1 до 5.\n");
    return 1;
  }

  // Вызов функции перевода числа
  convert_to_base2r(num, r);

  return 0;
}
