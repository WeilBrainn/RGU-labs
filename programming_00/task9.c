#include <stdio.h>

int main()
{
  double arr[10] = {1.1, 2.2, 3.3, 2.2, 4.4, 5.5, 1.1, 6.6, 7.7, 4.4};
  int size = 10;

  double unique_arr[10];
  int unique_count = 0;

  for (int i = 0; i < size; i++)
  {
    int is_unique = 1;

    for (int j = 0; j < unique_count; j++)
    {
      if (arr[i] == unique_arr[j])
      {
        is_unique = 0;
        break;
      }
    }

    if (is_unique)
    {
      unique_arr[unique_count] = arr[i];
      unique_count++;
    }
  }

  printf("Уникальные значения: ");
  for (int i = 0; i < unique_count; i++)
  {
    printf("%.1f ", unique_arr[i]);
  }
  printf("\n");

  return 0;
}
