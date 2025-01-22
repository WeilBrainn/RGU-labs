#ifndef OVERPRINTF_H
#define OVERPRINTF_H

#include <stdio.h>
#include <stdarg.h>

// Основные функции
int overprintf(const char *format, ...);
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

// Вспомогательная функция обработки
int v_over_handler(FILE *stream, char *str, const char *format, va_list args);

#endif // OVERPRINTF_H
