#include <stdio.h>
#include <ctype.h>

void rearrange_string(char *str)
{
  char *digits_ptr = str;
  char *letters_ptr = str;
  char *others_ptr = str;

  while (*others_ptr != '\0')
  {
    others_ptr++;
  }

  char temp[100];
  int d = 0, l = 0, o = 0;

  while (*str != '\0')
  {
    if (isdigit(*str))
    {
      temp[d++] = *str;
    }
    else if (isalpha(*str))
    {
      temp[d + l++] = *str;
    }
    else
    {
      temp[d + l + o++] = *str;
    }
    str++;
  }
  temp[d + l + o] = '\0';

  for (int i = 0; temp[i] != '\0'; i++)
  {
    str[i - (d + l + o)] = temp[i];
  }
}

int main()
{
  char str[] = "a1b2c3!@#def";
  rearrange_string(str);
  printf("Преобразованная строка: %s\n", str);
  return 0;
}
