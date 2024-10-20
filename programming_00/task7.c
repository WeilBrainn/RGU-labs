#include <stdio.h>

int main()
{
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = 10;

  int new_arr[5];
  int index = 0;

  for (int i = 1; i < size; i += 2)
  {
    new_arr[index] = arr[i];
    index++;
  }

  printf("Новый массив с числами с нечётных позиций: ");
  for (int i = 0; i < index; i++)
  {
    printf("%d ", new_arr[i]);
  }
  printf("\n");

  return 0;
}
