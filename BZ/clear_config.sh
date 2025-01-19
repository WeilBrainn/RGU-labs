#!/bin/bash

# Указать полный путь к файлу, который нужно удалить
file_to_delete="/home/max/Desktop/BZ/configure_file"

# Проверка существования файла перед удалением
if [ -e "$file_to_delete" ]; 
then
# Удаление файла
	rm "$file_to_delete"
	echo "File Deleted."
else
	echo "File doesnt exist."
fi