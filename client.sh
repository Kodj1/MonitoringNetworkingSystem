#!/bin/bash

# Собрать информацию об имени хоста
hostname=$(hostname)

# Собрать информацию о загрузке процессора
cpu_load=$(top -bn1 | grep "load average:" | awk '{print $10 $11 $12}')

# Собрать информацию об использовании оперативной памяти
memory_usage=$(free -h | grep "Mem:" | awk '{print $3 "/" $2}')

# Собрать информацию о дисковом пространстве
disk_usage=$(df -h / | grep "/" | awk '{print $3 "/" $2}')

# Собрать всю информацию в JSON-формате
data=$(cat <<EOF
{
    "hostname": "$hostname",
    "cpu_load": "$cpu_load",
    "memory_usage": "$memory_usage",
    "disk_usage": "$disk_usage"
}
EOF
)

# IP-адрес получателя
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
