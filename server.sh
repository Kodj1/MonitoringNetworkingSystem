#!/bin/bash

# Порт для прослушивания
port=8080

# Файл для сохранения полученных данных
output_file="received_data.txt"

# Запуск netcat для прослушивания на указанном порту и записи данных в файл
while true; do
    nc -l -p $port >> $output_file
done

if [ ! -f "$DATA_FILE" ]; then
  echo "Файл $DATA_FILE не найден!"
  exit 1
fi

# Чтение данных из файла
while IFS= read -r line
do
  # Предполагается, что данные в файле разделены пробелами и имеют формат:
  # node_id cpu_usage memory_usage network_in network_out
  NODE_ID=$(echo $line | awk '{print $1}')
  CPU_USAGE=$(echo $line | awk '{print $2}')
  MEMORY_USAGE=$(echo $line | awk '{print $3}')
  NETWORK_IN=$(echo $line | awk '{print $4}')
  NETWORK_OUT=$(echo $line | awk '{print $5}')
  COLLECTED_AT=$(date +'%Y-%m-%d %H:%M:%S')

  # Формирование SQL-запроса для вставки данных в таблицу metrics
  SQL_QUERY="INSERT INTO metrics (node_id, cpu_usage, memory_usage, network_in, network_out, collected_at) VALUES ('$NODE_ID', '$CPU_USAGE', '$MEMORY_USAGE', '$NETWORK_IN', '$NETWORK_OUT', '$COLLECTED_AT');"

  # Выполнение SQL-запроса с использованием psql
  psql -h 192.168.0.3 -d mns -U postgres -c "$SQL_QUERY"

done < "$DATA_FILE"
