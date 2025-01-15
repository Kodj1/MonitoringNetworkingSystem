#!/bin/bash

# Файл, содержащий данные
data_file="received_metrics.txt"

# Чтение данных из файла
network_in=$(grep "network_in=" $data_file | cut -d'=' -f2)
network_out=$(grep "network_out=" $data_file | cut -d'=' -f2)

# Вывод значений для проверки
echo "Network In: $network_in"
echo "Network Out: $network_out"