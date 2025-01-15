#!/bin/bash

# Порт для прослушивания входящих данных
LISTEN_PORT=8080

# Функция для обработки входящих данных
handle_data() {
    # Принять данные в формате JSON
    read json_data

    # Проверка, что json_data не пустой
    if [ -z "$json_data" ]; then
        echo "Получены пустые данные. Пропуск обработки."
        return
    fi
    
    # Используем jq для парсинга JSON-данных
    node_name=$(echo "$json_data" | jq -r '.node_name // empty')
    ip_address=$(echo "$json_data" | jq -r '.ip_address // empty')
    cpu_usage=$(echo "$json_data" | jq -r '.cpu_usage // empty')
    memory_usage=$(echo "$json_data" | jq -r '.memory_usage // empty')
    network_in=$(echo "$json_data" | jq -r '.network_in // empty')
    network_out=$(echo "$json_data" | jq -r '.network_out // empty')
    collected_at=$(date +'%Y-%m-%d %H:%M:%S')

    # Проверка, что все необходимые данные получены
    if [ -z "$node_name" ] || [ -z "$ip_address" ] || [ -z "$cpu_usage" ] || [ -z "$memory_usage" ] || [ -z "$network_in" ] || [ -z "$network_out" ]; then
        echo "Некоторые данные отсутствуют. Пропуск записи в базу данных."
        return
    fi
    
    # Формирование SQL-запроса для вставки данных в таблицу metrics
    SQL_QUERY=$(cat <<EOF
WITH node AS (
    INSERT INTO nodes (name, ip_address)
    VALUES ('$node_name', '$ip_address')
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

# Прослушивание порта и обработка входящих данных
while true; do
    # Используем nc для прослушивания порта и перенаправляем данные в handle_data
    nc -l -p $LISTEN_PORT | handle_data
done