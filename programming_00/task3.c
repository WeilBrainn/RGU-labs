#include <stdio.h>

void revurse_num1_num2(int num1, int num2, int *rev_num1, int *rev_num2)
{

  *rev_num1 = 0, *rev_num2 = 0;

  while (num1 > 0 || num2 > 0)
  {
    if (num1 > 0)
    {
      *rev_num1 = *rev_num1 * 10 + (num1 % 10);
      num1 /= 10;
    }
    if (num2 > 0)
    {
      *rev_num2 = *rev_num2 * 10 + (num2 % 10);
      num2 /= 10;
    }
  }
}

int main()
{
  int num1, num2, rev_num1, rev_num2;

  puts("Print number 1: \n");
  scanf("%d", &num1);

  puts("Print number 2: \n");
  scanf("%d", &num2);

  revurse_num1_num2(num1, num2, &rev_num1, &rev_num2);

  printf("Reverse number 1 and 2 of is %d, %d\n ", rev_num1, rev_num2);

  getchar();
  return 0;
