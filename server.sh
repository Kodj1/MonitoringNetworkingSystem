#!/bin/bash

# Порт для прослушивания входящих данных
LISTEN_PORT=8080

# Функция для обработки входящих данных
handle_data() {
    # Принять данные в формате JSON
    read json_data
    
    # Используем jq для парсинга JSON-данных
    node_name=$(echo "$json_data" | jq -r '.node_name')
    ip_address=$(echo "$json_data" | jq -r '.ip_address')
    cpu_usage=$(echo "$json_data" | jq -r '.cpu_usage')
    memory_usage=$(echo "$json_data" | jq -r '.memory_usage')
    network_in=$(echo "$json_data" | jq -r '.network_in')
    network_out=$(echo "$json_data" | jq -r '.network_out')
    collected_at=$(date +'%Y-%m-%d %H:%M:%S')
    
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
    echo "$SQL_QUERY" | PGPASSWORD="your_password" psql -h 127.0.0.1 -d mns -U postgres

    # Проверка на успешное выполнение
    if [ $? -eq 0 ]; then
        echo "Данные успешно записаны в базу данных"
    else
        echo "Ошибка при записи данных в базу данных"
    fi
}

# Прослушивание порта и обработка входящих данных
while true; do
    nc -l -p $LISTEN_PORT -c 'handle_data'
done
