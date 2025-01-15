#!/bin/bash

# Адрес и порт сервера
SERVER_IP="127.0.0.1"
SERVER_PORT=8080

# Пример данных в формате JSON
json_data=$(cat <<EOF
{
  "node_name": "Node1",
  "ip_address": "192.168.1.1",
  "cpu_usage": 10,
  "memory_usage": 2048,
  "network_in": 300,
  "network_out": 200
}
EOF
)

# Отправка данных на сервер с использованием nc
echo "$json_data" | nc $SERVER_IP $SERVER_PORT