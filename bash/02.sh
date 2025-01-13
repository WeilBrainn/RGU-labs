#!/bin/bash

print_help() {
    echo "Используем: $0 [-e error_file] file1 file2 ..."
    echo "Этот скрипт подсчитывает общее количество строк в указанных файлах."
}

# Обработка аргументов
while getopts ":he:" opt; do
    case ${opt} in
        e) exec 2>"$OPTARG" ;;  # перенаправление ошибок
        h) print_help; exit 0 ;;
        \?) echo "Invalid option: -$OPTARG" >&2; exit 1 ;;
    esac
done

total_lines=0

# Подсчет строк в каждом указанном файле
for file in "$@"; do
    if [[ -f "$file" ]]; then
        lines=$(wc -l < "$file")
        total_lines=$((total_lines + lines))
    else
        echo "File $file not found." >&2
    fi
done

echo "Total lines: $total_lines"
