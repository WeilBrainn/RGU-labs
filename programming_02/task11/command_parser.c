#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Список доступных команд
const char *availableCommands[] = {"add", "mult", "sub", "pow", "div", "rem", "xor", "and", "or", "="};
#define COMMAND_COUNT (sizeof(availableCommands) / sizeof(availableCommands[0]))

// Выполнение команды (простейший пример для "add" и "sub")
int executeCommand(const char *command, char *args[], int argCount) {
    if (strcmp(command, "add") == 0 && argCount == 2) {
        int a = atoi(args[0]);
        int b = atoi(args[1]);
        printf("Result: %d\n", a + b);
        return 0;
    } else if (strcmp(command, "sub") == 0 && argCount == 2) {
        int a = atoi(args[0]);
        int b = atoi(args[1]);
        printf("Result: %d\n", a - b);
        return 0;
    } else {
        printf("Error: Unknown command or invalid arguments\n");
        return 1;
    }
}

// Функция парсинга входного файла
int parseInput(FILE *inputFile) {
    if (inputFile == NULL) {
        fprintf(stderr, "Error: Invalid input file\n");
        return 1; // Ошибка при открытии файла
    }

    char line[1024];
    char *args[10];  // Массив для аргументов команды
    int argCount = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = 0;

        // Пропускаем пустые строки
        if (line[0] == '\0')
            continue;

        // Получаем первую команду
        char *command = strtok(line, " \t");
        if (command == NULL)
            continue;

        // Проверяем, допустима ли команда
        int isValidCommand = 0;
        for (int i = 0; i < COMMAND_COUNT; i++) {
            if (strcmp(command, availableCommands[i]) == 0) {
                isValidCommand = 1;
                break;
            }
        }

        if (!isValidCommand) {
            fprintf(stderr, "Error: Invalid command '%s'\n", command);
            return 1; // Возврат ошибки
        }

        // Сбрасываем аргументы
        argCount = 0;

        // Получаем аргументы команды
        char *arg;
        while ((arg = strtok(NULL, " \t")) != NULL) {
            args[argCount++] = arg;
            if (argCount >= 10) {
                fprintf(stderr, "Error: Too many arguments for command '%s'\n", command);
                return 1; // Ошибка из-за переполнения массива аргументов
            }
        }

        // Выполнение команды
        if (executeCommand(command, args, argCount) != 0) {
            fprintf(stderr, "Error while executing command '%s'\n", command);
            return 1; // Ошибка выполнения команды
        }
    }

    return 0; // Успешное выполнение
}