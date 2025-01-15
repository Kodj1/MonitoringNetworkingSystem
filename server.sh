#!/bin/bash

# Порт для прослушивания
port=8080

# Файл для сохранения полученных данных
output_file="received_data.txt"

# Запуск netcat для прослушивания на указанном порту и записи данных в файл
while true; do
    nc -l -p $port >> $output_file
done
