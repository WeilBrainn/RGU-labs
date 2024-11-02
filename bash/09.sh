#!/bin/bash

# Функция для удаления файлов по списку
delete_files_from_list() {
    local list_file="$1"

    if [ ! -f "$list_file" ]; then
        echo "Файл со списком не найден: $list_file"
        exit 1
    fi

    echo "Удаляем файлы из списка в '$list_file':"

    while IFS= read -r file; do
        if [ -e "$file" ]; then
            rm "$file"
            echo "Удален файл: $file"
        else
            echo "Файл не найден: $file"
        fi
    done < "$list_file"
}

# Вызов функции с параметрами
delete_files_from_list "$@"
