#!/bin/bash

# Функция для поиска каталогов с указанным файлом
find_directories_with_file() {
    local filename="$1"
    local start_dir="."

    # Проверяем наличие ключа -d
    while getopts ":d:" opt; do
        case $opt in
            d) start_dir="$OPTARG" ;;
            \?) echo "Неверный ключ: -$OPTARG" >&2 ;;
        esac
    done

    # Перебираем подкаталоги и ищем файл
    echo "Ищу файл '$filename' в каталоге '$start_dir' и его подкаталогах:"
    find "$start_dir" -type f -name "$filename" -exec dirname {} \; | sort -u
}

# Вызов функции с параметрами
find_directories_with_file "$@"
