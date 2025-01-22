#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OK 0
#define UJASHO 1

typedef struct {
    int id;              // Целое неотрицательное число
    char name[100];      // Непустимая строка из букв латинского алфавита
    char surname[100];   // Непустимая строка из букв латинского алфавита
    float salary;        // Неотрицательное вещественное число
} Employee;

// Функция сравнения для сортировки по возрастанию
int compare_ascending(const void *a, const void *b) {
    const Employee *e1 = (const Employee *)a;
    const Employee *e2 = (const Employee *)b;

    if (e1->salary != e2->salary) {
        return (e1->salary > e2->salary) - (e1->salary < e2->salary);
    }
    int surname_cmp = strcmp(e1->surname, e2->surname);
    if (surname_cmp != 0) {
        return surname_cmp;
    }
    int name_cmp = strcmp(e1->name, e2->name);
    if (name_cmp != 0) {
        return name_cmp;
    }
    return e1->id - e2->id;
}

// Функция сравнения для сортировки по убыванию
int compare_descending(const void *a, const void *b) {
    const Employee *e1 = (const Employee *)a;
    const Employee *e2 = (const Employee *)b;

    if (e1->salary != e2->salary) {
        return (e2->salary > e1->salary) - (e2->salary < e1->salary);
    }
    int surname_cmp = strcmp(e2->surname, e1->surname);
    if (surname_cmp != 0) {
        return surname_cmp;
    }
    int name_cmp = strcmp(e2->name, e1->name);
    if (name_cmp != 0) {
        return name_cmp;
    }
    return e2->id - e1->id;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input_file> <-a/-d> <output_file>\n", argv[0]);
        return UJASHO;
    }

    // Проверка флага
    char *flag = argv[2];
    if (!(flag[0] == '-' || flag[0] == '/') || (flag[1] != 'a' && flag[1] != 'd')) {
        return UJASHO;
    }

    // Открытие входного файла
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        return UJASHO;
    }

    // Открытие выходного файла
    FILE *output_file = fopen(argv[3], "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return UJASHO;
    }

    // Считывание данных из входного файла
    Employee *employees = NULL;
    size_t count = 0;

    while (!feof(input_file)) {
        Employee emp;
        if (fscanf(input_file, "%d %99s %99s %f", &emp.id, emp.name, emp.surname, &emp.salary) != 4) {
            if (!feof(input_file)) {
                fprintf(stderr, "Error reading input file.\n");
                free(employees);
                fclose(input_file);
                fclose(output_file);
                return UJASHO;
            }
            break;
        }

        // Проверка данных
        if (emp.id < 0 || emp.salary < 0 || strlen(emp.name) == 0 || strlen(emp.surname) == 0 ||
            strspn(emp.name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(emp.name) ||
            strspn(emp.surname, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(emp.surname)) {
            fprintf(stderr, "Invalid data format in input file.\n");
            free(employees);
            fclose(input_file);
            fclose(output_file);
            return UJASHO;
        }

        // Добавление сотрудника в массив
        Employee *temp = realloc(employees, (count + 1) * sizeof(Employee));
        if (temp == NULL) {
            perror("Memory allocation failed");
            free(employees);
            fclose(input_file);
            fclose(output_file);
            return UJASHO;
        }
        employees = temp;
        employees[count] = emp;
        count++;
    }

    fclose(input_file);

    // Сортировка данных
    if (flag[1] == 'a') {
        qsort(employees, count, sizeof(Employee), compare_ascending);
    } else {
        qsort(employees, count, sizeof(Employee), compare_descending);
    }

    // Запись отсортированных данных в выходной файл
    for (size_t i = 0; i < count; i++) {
        fprintf(output_file, "%d %s %s %.2f\n",
                employees[i].id, employees[i].name, employees[i].surname, employees[i].salary);
    }

    fclose(output_file);
    free(employees);

    return OK;
}
