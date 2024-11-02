#!/bin/bash

# Функция для проверки файлов по количеству слов
check_file_word_count() {
    local word_count_limit="$1"
    shift

    echo "Ищем файлы с количеством слов больше $word_count_limit в указанных каталогах:"

    for dir in "$@"; do
        if [ -d "$dir" ]; then
            echo "Проверяем каталог: $dir"
            find "$dir" -type f | while read -r file; do
                local word_count=$(wc -w < "$file")
                if [ "$word_count" -gt "$word_count_limit" ]; then
                    echo "Файл: $file (Количество слов: $word_count)"
                fi
            done
        else
            echo "Каталог не найден: $dir"
        fi
    done
}

# Вызов функции с параметрами
check_file_word_count "$@"
