#include <stdio.h>
#include <stdarg.h>
#define IS_CONVEX 1
#define NOT_CONVEX 0
#define UJASHO -1

// Структура для хранения координат точки
typedef struct
{
  double x, y;
} Point;

// Функция для вычисления векторного произведения
// Если результат > 0: поворот против часовой стрелки
// Если результат < 0: поворот по часовой стрелке
// Если результат == 0: точки на одной линии
static double cross_product(Point a, Point b, Point c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Функция проверки выпуклости
int is_convex_polygon(int num_points, ...)
{
  if (num_points < 3)
  {
    return UJASHO; // Многоугольник должен иметь как минимум 3 вершины
  }

  va_list args;
  va_start(args, num_points);

  // Считать координаты точек
  Point points[num_points];
  for (int i = 0; i < num_points; i++)
  {
    points[i].x = va_arg(args, double);
    points[i].y = va_arg(args, double);
  }
  va_end(args);

  // Определяем выпуклость
  int has_positive = 0;
  int has_negative = 0;

  for (int i = 0; i < num_points; i++)
  {
    Point a = points[i];
    Point b = points[(i + 1) % num_points];
    Point c = points[(i + 2) % num_points];

    double cross = cross_product(a, b, c);
    if (cross > 0)
    {
      has_positive = 1;
    }
    else if (cross < 0)
    {
      has_negative = 1;
    }

    if (has_positive && has_negative)
    {
      return NOT_CONVEX; // Если есть как положительные, так и отрицательные значения, то многоугольник не выпуклый
    }
  }

  return IS_CONVEX; // Все углы либо только положительные, либо только отрицательные
}

int main()
{
  int result;

  result = is_convex_polygon(4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0);
  if (result == IS_CONVEX)
  {
    printf("Многоугольник выпуклый\n");
  }
  else if (result == NOT_CONVEX)
  {
    printf("Многоугольник не является выпуклым\n");
  }
  else
  {
    printf("Недопустимый полигон\n");
  }

  result = is_convex_polygon(4, 0.0, 0.0, 2.0, 0.0, 1.0, 1.0, 0.0, 1.0);
  if (result == IS_CONVEX)
  {
    printf("Многоугольник выпуклый\n");
  }
  else if (result == NOT_CONVEX)
  {
    printf("Многоугольник не является выпуклым\n");
  }
  else
  {
    printf("Недопустимый полигон\n");
  }

  result = is_convex_polygon(2, 0.0, 0.0, 1.0, 1.0);
  if (result == IS_CONVEX)
  {
    printf("Многоугольник выпуклый\n");
  }
  else if (result == NOT_CONVEX)
  {
    printf("Многоугольник не является выпуклым\n");
  }
  else
  {
    printf("Недопустимый полигон\n");
  }

  return 0;
}
