#!/bin/bash

# Собрать информацию об имени хоста
hostname=$(hostname)

# Собрать информацию о загрузке процессора
cpu_load=$(top -bn1 | grep "load average:" | awk '{print $10 $11 $12}')

# Собрать информацию об использовании оперативной памяти
memory_usage=$(free -h | grep "Mem:" | awk '{print $3 "/" $2}')

# Собрать информацию о дисковом пространстве
disk_usage=$(df -h / | grep "/" | awk '{print $3 "/" $2}')

# Собрать информацию о сетевом трафике (пример, может потребовать доработки в зависимости от интерфейса)
network_in=$(ifconfig eth0 | grep "RX packets" | awk '{print $5}')
network_out=$(ifconfig eth0 | grep "TX packets" | awk '{print $5}')

# Собрать всю информацию в формате, который будет понят серверу
data=$(cat <<EOF
hostname=$hostname
cpu_load=$cpu_load
memory_usage=$memory_usage
disk_usage=$disk_usage
network_in=$network_in
network_out=$network_out
EOF
)

# IP-адрес и порт получателя
recipient_ip="192.168.0.3"
recipient_port="8080"

# Отправить данные на сервер с использованием netcat
echo "$data" | nc $recipient_ip $recipient_port

# Проверка результата отправки
if [ $? -eq 0 ]; then
    echo "Данные успешно отправлены на $recipient_ip:$recipient_port"
else
    echo "Ошибка при отправке данных на $recipient_ip:$recipient_port"
fi