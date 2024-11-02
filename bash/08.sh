#!/bin/bash

# Функция для вывода подкаталогов, отсортированных по размеру
list_sorted_subdirectories() {
    local start_dir="."

    # Проверка наличия ключа -d
    while getopts ":d:" opt; do
        case $opt in
            d) start_dir="$OPTARG" ;;
            \?) echo "Неверный ключ: -$OPTARG" >&2 ;;
        esac
    done

    echo "Подкаталоги в '$start_dir', отсортированные по размеру:"

    # Находим подкаталоги и выводим их размер
    find "$start_dir" -type d | while read -r dir; do
        local size=$(du -sh "$dir" | cut -f1)
        echo "$size $dir"
    done | sort -h
}

# Вызов функции с параметрами
list_sorted_subdirectories "$@"
