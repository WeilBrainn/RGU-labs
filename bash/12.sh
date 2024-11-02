#!/bin/bash

# Проверка, что передано хотя бы одно имя процесса
if [ "$#" -lt 1 ]; then
    echo "Использование: $0 [-s сигнал] имя_процесса1 [имя_процесса2 ...]"
    exit 1
fi

# Инициализация переменной для сигнала
signal=15  # По умолчанию сигнал SIGTERM

# Обработка параметров
while getopts ":s:" opt; do
    case $opt in
        s) signal="$OPTARG" ;;  # Установка сигнала
        \?) echo "Неверный ключ: -$OPTARG" >&2; exit 1 ;;
    esac
done

# Сдвигаем позиционные параметры, чтобы оставить только имена процессов
shift $((OPTIND - 1))

# Обработка имен процессов
for process_name in "$@"; do
    # Получение PID всех процессов с указанным именем
    pids=$(pgrep -f "$process_name")
    
    if [ -z "$pids" ]; then
        echo "Процесс \"$process_name\" не найден."
        continue
    fi

    # Отправка сигнала каждому PID
    for pid in $pids; do
        kill -s "$signal" "$pid" 2>/dev/null
        if [ $? -eq 0 ]; then
            echo "Отправлен сигнал $signal процессу $pid ($process_name)"
        else
            echo "Не удалось отправить сигнал процессу $pid ($process_name)"
        fi
    done
done
