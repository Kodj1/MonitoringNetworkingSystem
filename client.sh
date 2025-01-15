#!/bin/bash

# Собрать информацию об имени хоста и IP-адресе
hostname=$(hostname)
ip_address=$(hostname -I | awk '{print $1}')

# Собрать информацию о загрузке процессора
cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2 + $4}')

# Собрать информацию об использовании оперативной памяти
memory_usage=$(free -m | awk 'NR==2{printf "%.2f", $3*100/$2 }')

# Собрать информацию о сетевом трафике
network_in=$(cat /proc/net/dev | grep eth0 | awk '{print $2}')
network_out=$(cat /proc/net/dev | grep eth0 | awk '{print $10}')

# Собрать всю информацию в JSON-формате
data=$(cat <<EOF
{
    "node_name": "$hostname",
    "ip_address": "$ip_address",
    "cpu_usage": "$cpu_usage",
    "memory_usage": "$memory_usage",
    "network_in": "$network_in",
    "network_out": "$network_out"
}
EOF
)

# IP-адрес и порт получателя
recipient_ip="192.168.0.3"
recipient_port="8080"

# Отправить данные на другой IP-адрес с использованием netcat
echo "$data" | nc $recipient_ip $recipient_port

# Вывести результат отправки
if [ $? -eq 0 ]; then
    echo "Данные успешно отправлены на $recipient_ip:$recipient_port"
else
    echo "Ошибка при отправке данных на $recipient_ip:$recipient_port"
fi