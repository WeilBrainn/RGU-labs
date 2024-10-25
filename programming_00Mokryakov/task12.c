#include <stdio.h>
#include <stdlib.h>

void encryptDecrypt(const char *inputFile, const char *outputFile, char key)
{
  FILE *inFile = fopen(inputFile, "rb");
  FILE *outFile = fopen(outputFile, "wb");

  if (inFile == NULL || outFile == NULL)
  {
    printf("Ошибка при открытии файлов.\n");
    exit(1);
  }

  int byte;
  while ((byte = fgetc(inFile)) != EOF)
  {
    fputc(byte ^ key, outFile); // Шифруем/дешифруем каждый байт
  }

  fclose(inFile);
  fclose(outFile);
}

int main()
{
  char inputFile[100], outputFile[100], key;

  // Ввод имени файла и ключа
  printf("Введите имя входного файла: ");
  scanf("%s", inputFile);
  printf("Введите имя выходного файла: ");
  scanf("%s", outputFile);
  printf("Введите ключ (1 байт): ");
  scanf(" %c", &key); // Пробел перед %c для игнорирования пробелов

  // Шифрование/дешифрование
  encryptDecrypt(inputFile, outputFile, key);

  printf("Файл успешно зашифрован/расшифрован.\n");

  return 0;
}
