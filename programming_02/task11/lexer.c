#include "../includes/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

typedef struct
{
    char *key;   // указатель на строку для ключа
    char *value; // указатель на строку для значения
} KeyValuePair;

typedef struct
{
    KeyValuePair *pairs; // указатель на массмв пав
    int size;            // текущий размер массива
    int count;           // Колиество элементов в словаре
} Dictionary;

// функция для создания и инициализации словаря
Dictionary *createDictionary()
{
    Dictionary *dist = (Dictionary *)malloc(sizeof(Dictionary));
    if (dist == NULL)
    {
        return NULL;
    }
    dist->pairs = (KeyValuePair *)malloc(sizeof(KeyValuePair) * INITIAL_SIZE);
    if (dist->pairs == NULL)
    {
        free(dist);
        return NULL;
    }
    dist->size = INITIAL_SIZE;
    dist->count = 0;
    return dist;
}

// добавление элементов в словарь
int addKeyValuePair(Dictionary *dist, const char *key, const char *value)
{
    if (dist->count >= dist->size)
    {
        // увеличим размер масс.
        int newSize = dist->size * 2;
        KeyValuePair *newPairs = (KeyValuePair *)realloc(dist->pairs, newSize * sizeof(KeyValuePair));
        if (newPairs == NULL)
        {
            return -1; // ошибка выделения памяти
        }
        dist->pairs = newPairs;
        dist->size = newSize;
    }
    // выделяем память и копируем ключ и значение
    dist->pairs[dist->count].key = strdup(key);
    dist->pairs[dist->count].value = strdup(value);

    if (dist->pairs[dist->count].key == NULL || dist->pairs[dist->count].value == NULL)
    {
        return -1; // ошибОчка выделения памяти
    }
    dist->count++;
    return 0; // успешное добавление
}

// функция поиска по значению
char *getValue(Dictionary *dist, const char *key)
{
    for (int i = 0; i < dist->count; i++)
    {
        if (strcmp(dist->pairs[i].key, key) == 0)
        {
            return dist->pairs[i].value;
        }
    }
    return NULL; // ключ не найден
}

void freeDictionary(Dictionary *dist)
{
    for (int i = 0; i < dist->count; i++)
    {
        free(dist->pairs[i].key);
        free(dist->pairs[i].value);
    }
    free(dist->pairs);
    free(dist);
}

// Функция удаления пробелов и игнорирования строк, начинающихся с '#'
char *deleteSpaces(char *text)
{
    int i, j = 0;
    int is_after_equals = 0;
    char *key;
    char *value;
    // Выделяем память для временной строки
    char *temp = (char *)malloc(sizeof(char) * (strlen(text) + 1));
    if (temp == NULL)
    {
        // Обработка ошибки выделения памяти
        return NULL;
    }


    // Проверка на пустую строку
    if (text[0] == '\0')
    {
        return NULL;
    }

    // Проверка, начинается ли строка с '#'
    if (text[0] == '#')
    {
        // Игнорируем всю строку
        return NULL;
    }


    for (i = 0; text[i] != '\0'; i++)
    {
        switch (text[i])
        {
        case '#':
            // если встретили # то завершим строку
            temp[j] = '\0';
            break; // выходим

        case '\n':
            // обработка новой строки
            temp[j] = '\0';
            j = 0;
            is_after_equals = 0;
            break;

        case '=':
            // обработка =
            temp[j] = '\0';
            key = strdup(temp);
            j = 0;
            is_after_equals = 1;
            break;

        case ' ':
            // обработка пробела
            if (is_after_equals)
            {
                temp[j++] = text[i];
            }
            break;

        default:
            // все остальные символы
            temp[j++] = text[i];
            break;
        }
    }
    temp[j] = '\0';

    // копируем обработанный текст обратно в исходную строку
    strcpy(text, temp);
    free(temp);
    return text;
}

// Функция чтения файла и запуск функции обработки всех строк
int readFile(const char *filename, char *buffer, size_t size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 1; // Ошибка при открытии файла
    }

    // Очищаем буфер перед использованием
    buffer[0] = '\0';
    char tempBuffer[1024]; // Временный буфер для каждой строки

    while (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL)
    {
        char *processedLine = deleteSpaces(tempBuffer);
        if (processedLine != NULL && strlen(processedLine) > 0)
        {
            // Добавляем обработанную строку в основной буфер
            strcat(buffer, processedLine);
            strcat(buffer, "\n"); // Добавляем перенос строки
        }
    }

    fclose(file);
    return 0;
}