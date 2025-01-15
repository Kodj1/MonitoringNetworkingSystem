#!/bin/bash

# Порт для прослушивания входящих данных
LISTEN_PORT=8080

# Функция для обработки входящих данных
handle_data() {
    local data_file="received_metrics.txt"
    cat > $data_file

    # Чтение данных из файла
    hostname=$(grep "hostname=" $data_file | cut -d'=' -f2)
    ip_address=$(grep "ip_address=" $data_file | cut -d'=' -f2)
    cpu_usage=$(grep "cpu_usage=" $data_file | cut -d'=' -f2)
    memory_usage=$(grep "memory_usage=" $data_file | cut -d'=' -f2)
    network_in=$(grep "network_in=" $data_file | cut -d'=' -f2)
    network_out=$(grep "network_out=" $data_file | cut -d'=' -f2)
    collected_at=$(date +'%Y-%m-%d %H:%M:%S')

    # Проверка на наличие значений в переменных
    if [[ -z "$hostname" || -z "$ip_address" || -z "$cpu_usage" || -z "$memory_usage" || -z "$network_in" || -z "$network_out" ]]; then
        echo "Некоторые переменные пусты. Пропуск вставки данных."
        return
    fi

    # Формирование SQL-запроса для вставки данных в таблицу metrics
    SQL_QUERY=$(cat <<EOF
WITH node AS (
    INSERT INTO nodes (name, ip_address)
    VALUES ('$hostname', '$ip_address')
    ON CONFLICT (ip_address) DO UPDATE SET name = EXCLUDED.name
    RETURNING id
)
INSERT INTO metrics (node_id, cpu_usage, memory_usage, network_in, network_out, collected_at)
VALUES ((SELECT id FROM node), $cpu_usage, $memory_usage, $network_in, $network_out, '$collected_at');
EOF
    )

    # Выполнение SQL-запроса с использованием psql
    echo "$SQL_QUERY" | PGPASSWORD="12345" psql -h 127.0.0.1 -d mns -U postgres

    # Проверка на успешное выполнение
    if [ $? -eq 0 ]; then
        echo "Данные успешно записаны в базу данных"
    else
        echo "Ошибка при записи данных в базу данных"
    fi
}

# Создаем именованный канал
fifo="/tmp/nc_fifo"
[ -p $fifo ] && rm $fifo
mkfifo $fifo

# Запускаем netcat и перенаправляем данные в именованный канал
nc -l -p $LISTEN_PORT < $fifo | handle_data > $fifo

# Удаляем именованный канал после завершения работы
rm $fifo