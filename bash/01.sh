#!/bin/bash

print_help() {
    echo "Используем: $0 [-e error_file]"
    echo "Этот скрипт выводит таблицу степеней от 0 до 6 для чисел от 1 до 9."
}

while getopts ":he:" opt; do
    case ${opt} in
        e) exec 2>"$OPTARG" ;;
        h) print_help; exit 0 ;;
        \?) echo "Ошибка: -$OPTARG" >&2; exit 1 ;;
    esac
done

# Генерация таблицы
for ((i=1; i<=9; i++)); do
    for ((j=0; j<=6; j++)); do
        printf "%d^%d = %d\n" "$i" "$j" $((i**j))
    done
done
