#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define UJASHO 1

struct Citizen
{
  char surname[100];
  char name[100];
  char patronymic[100];
  int day, month, year;
  char gender;
  float income;
  struct Citizen* next;
};

//функция для чтения файла
void load_from_file(FILE *file , struct Citizen** citizen)
{
  char surname[50], name[50], patronymic[50];
  int day, month, year;
  char gender;
  float income;

  FILE* file = fopen("filename.txt", "r");
  if (file == NULL)
  {
    return;
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file))
  {
    sscanf(buffer, "%s %s %s %d-%d-%d %c %f",
    surname, name, patronymic, &day, &month, &year, &gender, &income);

    struct Citizen* new_citizen = (struct Citizen*)malloc(sizeof(struct Citizen));
    if (new_citizen == NULL)
    {
      return;
    }

    strcpy(new_citizen->surname, surname);
    strcpy(new_citizen->name, name);
    strcpy(new_citizen->patronymic, patronymic);
    new_citizen->day = day;
    new_citizen->month = month;
    new_citizen->year = year;
    new_citizen->gender = gender;
    new_citizen->income = income;

    if (*citizen == NULL) {
      *citizen = new_citizen;
    }
  }
}

// функция поиска жителя
int search_citizen()
{

}

// функция изменения информации о жители
int edit_citizen()
{

}

// функция удаления о жители
int delete_citizen()
{

}

// фуНКЦИЯ добавления нового жителя
int add_new_citizen()
{

}

int main() {

  return OK;
}