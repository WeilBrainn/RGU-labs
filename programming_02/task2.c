#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "task2.h"

#define OK 0
#define UJASHO 1

typedef struct {
    char *array;
    size_t length;
} String;

char instance(char *data, String *str)
{
  if (data == NULL || str == NULL)
  {
    return '\0';
  }

  size_t length = strlen(data);

  char *new_data = (char *)malloc(length + 1);
  if (new_data == NULL)
  {
    return '\0';
  }

  strcpy(new_data, data);

  if (str->array != NULL)
  {
    free(str->array);
  }
  str->array = new_data;
  str->length = length;
  new_data[str->length] = '\0';

  return *new_data;
}

void clearString(String *str)
{
  if (str->array != NULL)
  {
    free(str->array);
  }
  str->array = NULL;
  str->length = 0;
}

int comparer(String *str, char *data)
{
  if (str == NULL || str->array == NULL || data == NULL)
  {
    return UJASHO;
  }

  if (strcmp(str->array, data) == 0)
  {
    return OK;
  }
  return UJASHO;
}

int equivalenceString(String *str, char *data)
{
  if (str == NULL || str->array == NULL || data == NULL)
  {
    return UJASHO;
  }

  int length1 = strlen(data);
  int length2 = strlen(str->array);
  if (length1 != length2)
  {
    return UJASHO;
  }
  if (strcmp(str->array, data) == 0)
  {
    return OK;
  }
  else
  {
    return UJASHO;
  }
}

int copyString(String *source, String *destination)
{
  if (source == NULL || source->array == NULL)
  {
    return UJASHO;
  }

  int length = strlen(source->array);
  if (destination->array != NULL)
  {
    free(destination->array);
  }
  char *new_destination = (char *)malloc(length + 1);
  if (new_destination == NULL)
  {
    return UJASHO;
  }

  strcpy(new_destination, source->array);
  destination->array = new_destination;
  destination->length = length;
  new_destination[destination->length] = '\0';

  return OK;
}

String *copyStringNew(String *source)
{
  if (source == NULL || source->array == NULL)
  {
    return NULL;
  }

  String *new_string = (String *)malloc(sizeof(String));
  if (new_string == NULL)
  {
    return NULL;
  }

  int length_source = strlen(source->array);
  char *new_array = (char *)malloc(length_source + 1);
  if (new_array == NULL)
  {
    free(new_string);
    return NULL;
  }

  strcpy(new_array, source->array);
  new_string->array = new_array;
  new_string->length = length_source;
  new_array[new_string->length] = '\0';

  return new_string;
}

String concatenate(const String *str1, const String *str2)
{
  String result;
  result.length = str1->length + str2->length;
  result.array = (char *)malloc(result.length + 1);
  if (result.array == NULL)
  {
    result.length = 0;
    return result;
  }

  memcpy(result.array, str1->array, str1->length);
  memcpy(result.array + str1->length, str2->array, str2->length);

  result.array[result.length] = '\0';
  return result;
}

int main()
{
  String str1;
  str1.array = (char *)malloc(6);
  if (str1.array == NULL)
  {
    return UJASHO;
  }
  strcpy(str1.array, "Hello");
  str1.length = 5;

  String str2;
  str2.array = (char *)malloc(6);
  if (str2.array == NULL)
  {
    free(str1.array);
    return UJASHO;
  }
  strcpy(str2.array, "World");
  str2.length = 5;

  String result = concatenate(&str1, &str2);
  if (result.array != NULL)
  {
    printf("Concatenated String: %s\n", result.array);
  }
  else
  {
    printf("Memory allocation failed for concatenated string.\n");
  }

  clearString(&str1);
  clearString(&str2);
  clearString(&result);

  return OK;
}
