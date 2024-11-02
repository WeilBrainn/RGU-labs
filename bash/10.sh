#!/bin/bash

# Файл настроек по умолчанию
config_file=".install-config"
# Параметры по умолчанию
default_path="$HOME"
default_mode="0644"
default_user="$(whoami)"
default_group="$(id -gn)"

# Обработка опций
while getopts ":o:p:m:u:g:a" opt; do
    case $opt in
        o) config_file="$OPTARG" ;;  # Указан файл настроек
        p) default_path="$OPTARG" ;;   # Изменение пути по умолчанию
        m) default_mode="$OPTARG" ;;    # Изменение прав доступа
        u) default_user="$OPTARG" ;;     # Изменение пользователя
        g) default_group="$OPTARG" ;;    # Изменение группы
        a) automate=true ;;              # Автоматизация
        \?) echo "Неверный ключ: -$OPTARG" >&2 ;;
    esac
done

shift $((OPTIND - 1))

# Указанный каталог
input_dir="$1"

# Проверка наличия каталога
if [ -z "$input_dir" ] || [ ! -d "$input_dir" ]; then
    echo "Необходимо указать корректный каталог."
    exit 1
fi

# Создание или обнуление файла настроек
> "$config_file"

# Сбор информации о файлах
for file in "$input_dir"/*; do
    if [ -f "$file" ]; then
        # Автоматизация: используем значения по умолчанию
        if [ "$automate" ]; then
            path="$default_path"
            mode="$default_mode"
            user="$default_user"
            group="$default_group"
        else
            # Запрос информации у пользователя
            read -p "Введите имя конечного каталога для '$file' [$default_path]: " path
            path="${path:-$default_path}"  # Если не введено, используем значение по умолчанию

            read -p "Введите права доступа для '$file' [$default_mode]: " mode
            mode="${mode:-$default_mode}"  # Если не введено, используем значение по умолчанию

            read -p "Введите имя пользователя для '$file' [$default_user]: " user
            user="${user:-$default_user}"  # Если не введено, используем значение по умолчанию

            read -p "Введите группу для '$file' [$default_group]: " group
            group="${group:-$default_group}"  # Если не введено, используем значение по умолчанию
        fi

        # Запись в файл настроек
        echo "$file : $mode : $user : $group" >> "$config_file"
        echo "Записано: $file : $mode : $user : $group"
    fi
done

echo "Информация записана в '$config_file'."
