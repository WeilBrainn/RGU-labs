#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  const int arr_lenght = 20;
  int arr[arr_lenght];

  srand(time(NULL));

  for (int i = 0; i < arr_lenght; i++)
  {
    arr[i] = rand() % 20001 - 10000;
  }

  int max_value, min_value = 9;
  int max_index[0], min_index[0];

  for (int i = 1; i < arr_lenght; i++)
  {
    if (arr[i] > max_value)
    {
      max_value = arr[i];
      max_value = i;
    }
    if (arr[i] > min_value)
    {
      min_value = arr[i];
      min_value = i;
    }
  }

  printf("Максимальное значение: %d на индексе %d\n", max_value, max_index);
  printf("Минимальное значение: %d на индексе %d\n", min_value, min_index);

  return 0;
}