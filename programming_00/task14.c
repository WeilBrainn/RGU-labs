#include <stdio.h>
#include <stdlib.h>

void find_max_min(int arr[], int arr_length, int *max_value, int *min_value, int *max_index, int *min_index)
{
  *max_value = arr[0];
  *min_value = arr[0];
  *max_index = 0;
  *min_index = 0;

  for (int i = 1; i < arr_length; i++)
  {
    if (arr[i] > *max_value)
    {
      *max_value = arr[i];
      *max_index = i;
    }
    if (arr[i] < *min_value)
    {
      *min_value = arr[i];
      *min_index = i;
    }
  }
}

int main()
{
  const int arr_length = 100;
  int arr[arr_length];
  int max_value, min_value, max_index, min_index;

  FILE *file = fopen("data.txt", "r");
  if (file == NULL)
  {
    printf("Ошибка открытия файла\n");
    return 1;
  }

  int i = 0;
  while (fscanf(file, "%d", &arr[i]) == 1 && i < arr_length)
  {
    i++;
  }

  fclose(file);

  find_max_min(arr, i, &max_value, &min_value, &max_index, &min_index);

  printf("Максимальное значение: %d на индексе %d\n", max_value, max_index);
  printf("Минимальное значение: %d на индексе %d\n", min_value, min_index);

  return 0;
}
