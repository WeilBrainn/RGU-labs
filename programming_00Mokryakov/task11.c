#include <stdio.h>

int main()
{
  unsigned int n;
  int len, i;

  // Ввод 2^p разрядного целого числа
  printf("Введите целое число: ");
  scanf("%u", &n);
  printf("Введите длину (количество битов): ");
  scanf("%d", &len);
  printf("Введите количество битов для склеивания (i): ");
  scanf("%d", &i);

  // A) Склеиваем первые i бит и последние i бит
  unsigned int firstBits = (n >> (len - i)) & ((1 << i) - 1); // Первые i бит
  unsigned int lastBits = n & ((1 << i) - 1);                 // Последние i бит

  // Объединяем их
  unsigned int gluedBits = (firstBits << i) | lastBits;

  // B) Получаем биты между первыми i и последними i
  unsigned int middleBits = (n >> i) & ((1 << (len - 2 * i)) - 1);

  // Вывод результатов
  printf("Склеенные биты: %u\n", gluedBits);
  printf("Биты между первыми и последними i битами: %u\n", middleBits);

  return 0;
}
