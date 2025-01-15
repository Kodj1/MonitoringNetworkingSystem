#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>

// Функция для получения использования CPU
double getCpuUsage() {
    std::ifstream file("/proc/stat");
    std::string line, cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    static long prev_user, prev_nice, prev_system, prev_idle, prev_iowait, prev_irq, prev_softirq, prev_steal;
    double usage;

    if (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

        long total_idle = idle + iowait;
        long prev_total_idle = prev_idle + prev_iowait;

        long total_non_idle = user + nice + system + irq + softirq + steal;
        long prev_total_non_idle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;

        long total = total_idle + total_non_idle;
        long prev_total = prev_total_idle + prev_total_non_idle;

        long total_diff = total - prev_total;
        long idle_diff = total_idle - prev_total_idle;

        usage = (total_diff - idle_diff) / static_cast<double>(total_diff) * 100;

        prev_user = user;
        prev_nice = nice;
        prev_system = system;
        prev_idle = idle;
        prev_iowait = iowait;
        prev_irq = irq;
        prev_softirq = softirq;
        prev_steal = steal;
    }

    return usage;
}

// Функция для получения использования памяти
double getMemoryUsage() {
    std::ifstream file("/proc/meminfo");
    std::string line, key;
    long value, total_memory, free_memory;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> key >> value;
        if (key == "MemTotal:") {
            total_memory = value;
        } else if (key == "MemAvailable:") {
            free_memory = value;
        }
    }

    return ((total_memory - free_memory) / static_cast<double>(total_memory)) * 100;
}

// Функция для получения сетевого трафика
void getNetworkUsage(double& networkIn, double& networkOut) {
    std::ifstream file("/proc/net/dev");
    std::string line, iface;
    long rx_bytes, tx_bytes;
    static long prev_rx_bytes, prev_tx_bytes;

    // Пропускаем первые две строки заголовков
    std::getline(file, line);
    std::getline(file, line);

    networkIn = 0;
    networkOut = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> iface >> rx_bytes;
        ss.ignore(64, ' '); // Пропускаем ненужные поля
        ss >> tx_bytes;

        if (iface != "lo:") { // Игнорируем loopback интерфейс
            networkIn += rx_bytes;
            networkOut += tx_bytes;
        }
    }

    networkIn -= prev_rx_bytes;
    networkOut -= prev_tx_bytes;

    prev_rx_bytes += networkIn;
    prev_tx_bytes += networkOut;
}

// Функция для отправки данных на сервер
void sendDataToServer(const std::string& serverIp, int serverPort, const std::string& data) {
    // Создаем сокет
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    // Устанавливаем адрес сервера
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported." << std::endl;
        close(sock);
        return;
    }

    // Подключаемся к серверу
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        close(sock);
        return;
    }

    // Отправляем данные на сервер
    send(sock, data.c_str(), data.size(), 0);
    std::cout << "Data sent: " << data << std::endl;

    // Закрываем сокет
    close(sock);
}

int main() {
    std::string serverIp = "127.0.0.1"; // IP-адрес сервера
    int serverPort = 8080; // Порт сервера

    // Получаем системные метрики
    int nodeId = 1; // Предположим, что nodeId фиксированный для данного узла
    double cpuUsage = getCpuUsage();
    double memoryUsage = getMemoryUsage();
    double networkIn, networkOut;
    getNetworkUsage(networkIn, networkOut);

    // Формируем строку данных в формате nodeId,cpuUsage,memoryUsage,networkIn,networkOut
    std::ostringstream dataStream;
    dataStream << nodeId << "," << cpuUsage << "," << memoryUsage << "," << networkIn << "," << networkOut;
    std::string data = dataStream.str();

    // Отправляем данные на сервер
    sendDataToServer(serverIp, serverPort, data);

    return 0;
}