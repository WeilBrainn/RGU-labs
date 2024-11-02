#!/bin/bash

# Параметры по умолчанию
default_mode="0644"
default_user="$(whoami)"
default_group="$(id -gn)"

# Обработка опций
while getopts ":m:M:u:U:g:G:" opt; do
    case $opt in
        m) default_mode="$OPTARG" ;;  # Изменение прав доступа по умолчанию
        M) mode_all="$OPTARG" ;;       # Изменение всех прав доступа на указанный
        u) default_user="$OPTARG" ;;    # Изменение пользователя по умолчанию
        U) user_all="$OPTARG" ;;        # Изменение всех пользователей на указанный
        g) default_group="$OPTARG" ;;   # Изменение группы по умолчанию
        G) group_all="$OPTARG" ;;       # Изменение всех групп на указанную
        \?) echo "Неверный ключ: -$OPTARG" >&2 ;;
    esac
done

shift $((OPTIND - 1))

# Проверка наличия входного файла
input_file="$1"
if [ ! -f "$input_file" ]; then
    echo "Укажите корректный файл для чтения параметров."
    exit 1
fi

# Чтение строк из файла
while IFS=" : " read -r path mode user group; do
    # Проверка на пустые значения и установка значений по умолчанию
    path=${path:-}
    mode=${mode:-$default_mode}
    user=${user:-$default_user}
    group=${group:-$default_group}

    # Если указаны значения для всех прав, пользователя и группы, то заменяем их
    if [[ -n "$mode_all" ]]; then
        mode="$mode_all"
    fi
    if [[ -n "$user_all" ]]; then
        user="$user_all"
    fi
    if [[ -n "$group_all" ]]; then
        group="$group_all"
    fi

    # Создание каталога (если необходимо) и файла
    dir_name=$(dirname "$path")
    mkdir -p "$dir_name"

    # Создание файла
    touch "$path"

    # Установка прав доступа
    chmod "$mode" "$path"

    # Установка пользователя и группы
    chown "$user:$group" "$path"

    echo "Создан файл: $path с правами $mode, пользователь: $user, группа: $group"
done < "$input_file"
