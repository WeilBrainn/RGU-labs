#include <stdio.h>
#include <ctype.h>

void remove_non_letters(char *str)
{
  char *src = str;
  char *dst = str;

  while (*src != '\0')
  {
    if (isalpha(*src))
    {
      *dst = *src;
      dst++;
    }
    src++;
  }
  *dst = '\0';
}

int main()
{
  char str[] = "H3llo, W@orld!";
  remove_non_letters(str);
  printf("Результат: %s\n", str);
  return 0;
}
