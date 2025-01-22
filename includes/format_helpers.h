#ifndef FORMAT_HELPERS_H
#define FORMAT_HELPERS_H

#include <stdio.h>

// Обработка нестандартных форматов
size_t print_roman(int num, FILE *stream, char *str);
size_t print_zeckendorf(unsigned int num, FILE *stream, char *str);
size_t convert_to_base(int num, int base, int uppercase, FILE *stream, char *str);
size_t convert_to_decimal(const char *num_str, int base, int uppercase, FILE *stream, char *str);
size_t memory_dump(void *data, char type, FILE *stream, char *str);

#endif // FORMAT_HELPERS_H