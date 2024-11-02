#!/bin/bash

print_help() {
    echo "Используем: $0 [-e error_file] [-d directory]"
    echo "Этот скрипт подсчитывает количество файлов в указанном каталоге."
}

directory="."

# Обработка аргументов
while getopts ":he:d:" opt; do
    case ${opt} in
        e) exec 2>"$OPTARG" ;;  # перенаправление ошибок
        d) directory="$OPTARG" ;;
        h) print_help; exit 0 ;;
        \?) echo "Invalid option: -$OPTARG" >&2; exit 1 ;;
    esac
done

# Подсчет файлов
count=$(find "$directory" -type f | wc -l)
echo "Total files in '$directory': $count"
