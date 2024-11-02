#!/bin/bash

# Функция для создания жёстких ссылок
create_hard_links() {
    local files=("$@")
    local base_name
    local extension
    local link_number

    for file in "${files[@]}"; do
        if [ -f "$file" ]; then
            base_name="${file%.*}"
            extension="${file##*.}"
            link_number=1

            # Создание жёсткой ссылки
            while [ -e "${base_name}.${link_number}" ]; do
                link_number=$((link_number + 1))
                if [ "$link_number" -gt 9 ]; then
                    echo "Все ссылки до .9 уже существуют для файла: $file"
                    break
                fi
            done

            # Создание новой жёсткой ссылки, если возможно
            if [ "$link_number" -le 9 ]; then
                ln "$file" "${base_name}.${link_number}"
                echo "Создана жёсткая ссылка: ${base_name}.${link_number}"
            fi
        else
            echo "Файл не найден: $file"
        fi
    done
}

# Удаление жёстких ссылок при использовании -r
remove_hard_links() {
    local files=("$@")

    for file in "${files[@]}"; do
        for i in {1..9}; do
            if [ -e "${file}.${i}" ]; then
                rm "${file}.${i}"
                echo "Удалена жёсткая ссылка: ${file}.${i}"
            fi
        done
    done
}

# Основная часть скрипта
while getopts ":r" opt; do
    case $opt in
        r) remove_hard_links "${@:OPTIND}" ;;
        \?) echo "Неверный ключ: -$OPTARG" >&2 ;;
    esac
done

shift $((OPTIND - 1))

create_hard_links "$@"
