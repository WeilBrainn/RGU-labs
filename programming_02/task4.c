#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OK 0
#define UJASHO 1

typedef struct {
    unsigned int id;
    char *name;
    char *surname;
    char *group;
    unsigned char *grades; // массив из 5 оценок
} Student;

typedef struct {
    Student *students; // указатель на массив студентов
    size_t count;      // текущее количество студентов
} StudentArray;

// Функция для чтения студентов из файла
int read_students_from_file(StudentArray *array, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return UJASHO;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Student student;

        // Разбор строки
        char *token = strtok(buffer, " ");
        student.id = strtoul(token, NULL, 10);
        if (student.id == 0) {
            fclose(file);
            return UJASHO;
        }

        token = strtok(NULL, " ");
        student.name = strdup(token);
        if (student.name == NULL) {
            fclose(file);
            return UJASHO;
        }

        token = strtok(NULL, " ");
        student.surname = strdup(token);
        if (student.surname == NULL) {
            free(student.name);
            fclose(file);
            return UJASHO;
        }

        token = strtok(NULL, " ");
        student.group = strdup(token);
        if (student.group == NULL) {
            free(student.name);
            free(student.surname);
            fclose(file);
            return UJASHO;
        }

        student.grades = (unsigned char *)malloc(5 * sizeof(unsigned char));
        if (student.grades == NULL) {
            free(student.name);
            free(student.surname);
            free(student.group);
            fclose(file);
            return UJASHO;
        }

        for (int i = 0; i < 5; i++) {
            token = strtok(NULL, " ");
            student.grades[i] = (unsigned char)strtoul(token, NULL, 10);
        }

        // Добавление студента в массив
        Student *new_students = (Student *)realloc(array->students, (array->count + 1) * sizeof(Student));
        if (new_students == NULL) {
            free(student.name);
            free(student.surname);
            free(student.group);
            free(student.grades);
            fclose(file);
            return UJASHO;
        }

        array->students = new_students;
        array->students[array->count] = student;
        array->count++;
    }

    fclose(file);
    return OK;
}

// Поиск студента по id
Student *find_student_by_id(StudentArray *array, unsigned int id) {
    for (size_t i = 0; i < array->count; i++) {
        if (array->students[i].id == id) {
            return &array->students[i];
        }
    }
    return NULL;
}

// Поиск студента по фамилии
Student *find_student_by_surname(StudentArray *array, const char *surname) {
    for (size_t i = 0; i < array->count; i++) {
        if (strcmp(array->students[i].surname, surname) == 0) {
            return &array->students[i];
        }
    }
    return NULL;
}

// Сортировка по id
int compare_id(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return (s1->id - s2->id);
}

// Сортировка по фамилии
int compare_surname(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->surname, s2->surname);
}

// Сортировка массива студентов
void sort_students(StudentArray *array, int (*compare)(const void *a, const void *b)) {
    qsort(array->students, array->count, sizeof(Student), compare);
}

// Функция для записи средней оценки студентов в файл
void write_students_to_trace(StudentArray *array, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла для записи\n");
        return;
    }

    for (size_t i = 0; i < array->count; i++) {
        Student *student = &array->students[i];
        int sum = 0;

        for (int j = 0; j < 5; j++) {
            sum += student->grades[j];
        }

        float average = sum / 5.0;
        fprintf(file, "ID: %u, Name: %s %s, Group: %s, Average Grade: %.2f\n",
                student->id, student->name, student->surname, student->group, average);
    }

    fclose(file);
}

// Очистка памяти, занятой массивом студентов
void free_student_array(StudentArray *array) {
    for (size_t i = 0; i < array->count; i++) {
        free(array->students[i].name);
        free(array->students[i].surname);
        free(array->students[i].group);
        free(array->students[i].grades);
    }
    free(array->students);
    array->students = NULL;
    array->count = 0;
}

int main(int argc, char *argv[]) {
    StudentArray array = {NULL, 0};

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return UJASHO;
    }

    if (read_students_from_file(&array, argv[1]) != OK) {
        fprintf(stderr, "Ошибка чтения файла\n");
        return UJASHO;
    }

    sort_students(&array, compare_id);
    write_students_to_trace(&array, "students_trace.txt");

    free_student_array(&array);
    return OK;
}
