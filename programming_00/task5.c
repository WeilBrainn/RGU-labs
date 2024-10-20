#include <stdio.h>

int binary_search(int arr[], int size, int target)
{
  int left = 0;
  int right = size - 1;

  while (left <= right)
  {
    int mid = (left + right) / 2;

    if (arr[mid] == target)
    {
      return mid;
    }

    if (arr[mid] < target)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return -1;
}

int main()
{
  int arr[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
  int size = 10;

  int target;
  printf("Введите элемент для поиска: ");
  scanf("%d", &target);

  int result = binary_search(arr, size, target);

  if (result != -1)
  {
    printf("Элемент %d найден на индексе %d\n", target, result);
  }
  else
  {
    printf("Элемент %d не найден в массиве\n", target);
  }

  return 0;
}
