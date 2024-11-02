#!/bin/bash

# Функция для создания жёстких или символических ссылок на файлы с заданной строкой
create_links() {
    local search_string="$1"
    local target_dir="."
    local use_symlinks=false

    # Обработка опций
    while getopts ":o:s" opt; do
        case $opt in
            o) target_dir="$OPTARG" ;;
            s) use_symlinks=true ;;
            \?) echo "Неверный ключ: -$OPTARG" >&2 ;;
        esac
    done

    shift $((OPTIND - 1))

    local search_dir="$1"

    if [ -z "$search_dir" ]; then
        echo "Не указан каталог для поиска."
        exit 1
    fi

    # Поиск файлов и создание ссылок
    find "$search_dir" -type f | while read -r file; do
        if grep -q "$search_string" "$file"; then
            local link_name="${target_dir}/$(basename "$file")"
            if $use_symlinks; then
                ln -s "$file" "$link_name"
                echo "Создана символическая ссылка: $link_name"
            else
                ln "$file" "$link_name"
                echo "Создана жёсткая ссылка: $link_name"
            fi
        fi
    done
}

# Вызов функции с параметрами
create_links "$@"
