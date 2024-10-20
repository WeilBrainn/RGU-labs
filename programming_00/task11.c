#include <stdio.h>

int my_strlen(const char *str)
{
  int length = 0;
  while (str[length] != '\0')
  {
    length++;
  }
  return length;
}

int main()
{
  char str[] = "Hello, world!";
  printf("Длина строки: %d\n", my_strlen(str));
  return 0;
}
