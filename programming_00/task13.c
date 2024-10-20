#include <stdio.h>
#include <ctype.h>

void convert_odd_to_uppercase(char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (i % 2 != 0)
    {
      str[i] = toupper(str[i]);
    }
  }
}

int main()
{
  char str[] = "hello world";
  convert_odd_to_uppercase(str);
  printf("Результат: %s\n", str);
  return 0;
}
