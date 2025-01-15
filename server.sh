#!/bin/bash

# Порт для прослушивания входящих данных
LISTEN_PORT=8080

# Функция для обработки входящих данных
handle_data() {
    # Принять данные из файла
    data_file="received_metrics.txt"
    cat > $data_file
    
# Чтение данных из файла
    hostname=$(grep "hostname=" $data_file | cut -d'=' -f2)
    ip_address=$(grep "ip_address=" $data_file | cut -d'=' -f2)
    cpu_usage=$(grep "cpu_usage=" $data_file | cut -d'=' -f2)
    memory_usage=$(grep "memory_usage=" $data_file | cut -d'=' -f2)
    network_in=$(grep "network_in=" $data_file | cut -d'=' -f2)
    network_out=$(grep "network_out=" $data_file | cut -d'=' -f2)
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
    nc -l -p $LISTEN_PORT -c 'handle_data'
done
