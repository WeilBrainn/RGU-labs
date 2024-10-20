#include <stdio.h>

char *my_strstr(const char *haystack, const char *needle)
{
  if (!*needle)
  {
    return (char *)haystack;
  }

  for (int i = 0; haystack[i] != '\0'; i++)
  {
    int j = 0;
    while (haystack[i + j] == needle[j] && needle[j] != '\0')
    {
      j++;
    }
    if (needle[j] == '\0')
    {
      return (char *)&haystack[i];
    }
  }
  return NULL;
}

int main()
{
  char str[] = "Hello, world!";
  char substr[] = "world";
  char *result = my_strstr(str, substr);
  if (result != NULL)
  {
    printf("Подстрока найдена: %s\n", result);
  }
  else
  {
    printf("Подстрока не найдена\n");
  }
  return 0;
}
