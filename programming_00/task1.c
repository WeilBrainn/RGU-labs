#include <stdio.h>

int main() {
  int arr[5] = {2,12,3,4,55};
  int  i, j, q = 0;
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 5 - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          q = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = q;
        }
      }
    }

  for (i = 0; i < 5; i++) {
    printf("%d\n", arr[i]);
  }

  return 0;
}