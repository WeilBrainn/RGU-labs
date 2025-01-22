#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define UJASHO 1
#define NULL_MATRIX 1
#define NULL_ROW 2
#define NULL_STORAGE 3
#define NULL_COUNT_STORAGE 4
#define NULL_COMPARER 5
#define MEMORY_ERROR 6

typedef int tvalue;

int comparer(const tvalue *a, const tvalue *b, int is_strict) {
    if (is_strict) {
        return (*a > *b) - (*a < *b);  // Строгое сравнение
    } else {
        return (*a >= *b) - (*a <= *b); // Нестрогое сравнение
    }
}

int add_saddle_point(size_t ***storage, size_t *count, size_t row, size_t col);
{
  // выделяем память
  size_t **new_storage = (size_t)realoc(*storage, (*count + 1) * sizeof(size_t *));
  // чекаем выделение
  if (new_storage == NULL)
  {
    return UJASHO;
  }

  // выделим память для хранения новой точки
  (*storage)[*count] = (*storage)malloc(2 * sizeof(size_t));
  if ((*storage)[*count] == NULL)
  {
    return UJASHO;
  }

  // записываем корды
  (*storage)[*count][0] = row;
  (*storage)[*count][1] = col;
  (*count)++;
  return OK;
}

int is_min_in_row(tvalue const *row, size_t row_length, tvalue const *element, int (*comparer)(tvalue const *, tvalue const *), int is_comparison_is_strict);
{
  for (size_t i = 0; i < row_length; i++)
  {
    if (is_comparison_is_strict)
    {
      if (comparer(element, &row[i]) >= 0))
      {
          // не минимальный
          return OK;
      }
      else
      {
        if (comparer(element, &row[i]) > 0))
        {
		  // не минимальный
          return OK;
        }
      }
    }
  }
  return 1; // минимальный
}

int is_max_in_column(tvalue const * const *matrix, size_t matrix_rows_count, size_t column_index, tvalue const *element, int (*comparer)(tvalue const *, tvalue const *), int is_comparison_is_strict);
{
  for (size_t i = 0; i < matrix_rows_count; i++)
  {
    if (is_comparison_is_strict)
    {
      if (comparer(element, &matrix[i][column_index]) <= 0)
      {
        return OK; // Не максимальный
      }
      if (comparer(element, &matrix[i][column_index]) < 0)
      {
        return OK; // Не максимальный
      }
    }
  }
  return 1; // максимальный
}

int find_saddle_points(
    tvalue const * const *matrix,
    size_t matrix_rows_count,
    size_t matrix_columns_count,
    size_t ***found_saddle_points_storage,
    size_t *found_saddle_points_count_storage,
    int (*comparer)(tvalue const *, tvalue const *),
    int is_comparison_is_strict
)
{
  	int is_max_in_col, is_min_in_row;
	tvalue current;
  	size_t current_row = 0, current_col = 0;

  // базированная проверка
  if (
      !matrix||
      !found_saddle_points_storage||
      !found_saddle_points_count_storage||
      !comparer
  )
  {
    return NULL_MATRIX;
  }

  // проверка что каждая строчка матрицы корректна
  for(size_t i = 0; i < matrix_rows_count; i++)
  {
    if (!matrix[i])
    {
      return NULL_ROW;
    }
  }

  *found_saddle_points_storage = NULL;
  *found_saddle_points_count_storage = 0;

  // поиск седловых точек
  for (size_t i = 0; i < matrix_rows_count; i++)
  {
    for (size_t j = 0; j < matrix_columns_count; j++)
    {
      tvalue const *current = &matrix[i][j];
      if (is_min_in_row(matrix[i], matrix_columns_count, current, comparer, is_comparison_is_strict) &&
      is_max_in_column(matrix, matrix_rows_count, j, current, comparer, is_comparison_is_strict)) {
      int result = add_saddle_point(found_saddle_points_storage,
      found_saddle_points_count_storage, i, j);
        if (result != OK) {
          return MEMORY_ERROR;
        }
      }
    }
  }
  return OK;
}

void free_saddle_points(size_t **storage, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    free(storage[i]);
  }
  free(storage);
}

int main()
{
  tvalue matrix_data[3][3] =
  {
    {3, 1, 2},
    {6, 4, 5},
    {7, 8, 9},
  };

  // преобразуем в указатель на массив указателей
  tvalue *matrix[3];
  for (size_t i = 0; i < 3; i++)
  {
    matrix[i] = matrix_data[i]
  }

  // хранилище для результатов
  size_t **saddle_points = NULL;
  size_t saddle_points_count = 0;

  // туть вызовы функции
  int result = find_saddle_points
  (
  (tvalue const * const *)matrix, 3, 3,
  &saddle_points, &saddle_points_count,
  comparer, 1 // строгое сравнение
  )

	// Проверка результата
    if (result == OK) {
        printf("Найдено седловых точек: %zu\n", saddle_points_count);
        for (size_t i = 0; i < saddle_points_count; i++) {
            printf("Седловая точка: строка %zu, колонка %zu\n",
                   saddle_points[i][0], saddle_points[i][1]);
        }
    } else {
        printf("Ошибка: %d\n", result);
    }

  // чистим память
  free_saddle_points(saddle_points, saddle_points_count);

  return OK;
}