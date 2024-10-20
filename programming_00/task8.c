#include <stdio.h>

int main()
{
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = 10;

  int even_arr[10];
  int index = 0;

  for (int i = 0; i < size; i++)
  {
    if (arr[i] % 2 == 0)
    {
      even_arr[index] = arr[i];
      index++;
    }
  }

  printf("Чётные числа: ");
  for (int i = 0; i < index; i++)
  {
    printf("%d ", even_arr[i]);
  }
  printf("\n");

  return 0;
}
