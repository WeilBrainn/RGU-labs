#include "overprintf.h"
#include "format_helpers.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int over_printf(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  int result = v_over_handler(stdout, NULL, format, args);
  va_end(args);
  return result;
}

int over_fprintf(FILE *stream, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  int result = v_over_handler(stream, NULL, format, args);
  va_end(args);
  return result;
}

int over_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int result = v_over_handler(NULL, str, format, args);
  va_end(args);
  return result;
}

// тута основная функция для обработки
int v_over_handler(FILE *stream, char *str, const char *format, va_list args)
{
  char buffer[1024];
  size_t pos = 0;
  const char *ptr = format;

  while(*ptr)
  {
    if(*ptr == '%' && *(ptr + 1) != '\0')
    {
      ptr++;
      switch(*ptr)
      {
        case 'R': // %Ro
          if (*(ptr + 1) == 'o')
            {
              int num = va_arg(args, int);
              pos += print_roman(num, stream, str ? &str[pos] : NULL);
              ptr++;
            }
            break;
        case 'Z': // %Zr
          if (*(ptr + 1) == 'r')
          {
            unsigned int num = va_arg(args, unsigned int);
            pos += print_zeckendorf(num, stream, str ? &str[pos] : NULL);
            ptr++;
          }
          break;
        case 'C': // %Cv, %CV
          if (*(ptr + 1) == 'v' || *(ptr + 1) == 'V')
            {
              int num = va_arg(args, int);
              int base = va_arg(args, int);
              if (base < 2 || base > 36)
                {
                  base = 10;
                }
              pos += convert_to_base(num, base, *(ptr + 1) == 'V', stream, str ? &str[pos] : NULL);
              ptr++;
            }
            break;
        case 't': // %to, %TO
          if (*(ptr + 1) == 'o' || *(ptr + 1) == 'O') {
            char *num_str = va_arg(args, char *);
            int base = va_arg(args, int);
            if (base < 2 || base > 36) base = 10;
            pos += convert_to_decimal(num_str, base, *(ptr + 1) == 'O', stream, str ? &str[pos] : NULL);
            ptr++;
          }
          break;
        case 'm': // %mi, %mu, %md, %mf
          switch (*(ptr + 1))
          {
            case 'i': // %mi
            case 'u': // %mu
            case 'd': // %md
            case 'f': // %mf
            pos += memory_dump(va_arg(args, void *), *(ptr + 1), stream, str ? &str[pos] : NULL);
            ptr++;
            break;
          }
          break;
        default:
          buffer[pos++] = '%';
          buffer[pos++] = *ptr;
          break;
      }
    }
    else {
      buffer[pos++] = *ptr;
    }
    ptr++;
  }

  buffer[pos] = '\0';
  if (str) strcpy(str, buffer);
  else if (stream) fputs(buffer, stream);

  return pos;
}