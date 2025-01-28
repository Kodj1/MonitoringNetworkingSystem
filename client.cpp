#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <libpq-fe.h>

// Функция для получения использования CPU и полного объема CPU
void getCpuUsage(double& cpuUsage, double& totalCpu) {
    std::ifstream file("/proc/stat");
    std::string line, cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    static long prev_user, prev_nice, prev_system, prev_idle, prev_iowait, prev_irq, prev_softirq, prev_steal;
    double usage;

    if (std::getline(file, line) && line.substr(0, 3) == "cpu") { // Проверка, что строка начинается с "cpu"
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

        cpuUsage = usage;
        totalCpu = 100.0; // Полный объем CPU всегда 100%
    }
}

// Функция для получения использования памяти и полного объема памяти
void getMemoryUsage(double& memoryUsage, double& totalMemory) {
    std::ifstream file("/proc/meminfo");
    std::string line, key;
    long value, total_memory = 0, free_memory = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> key >> value;
        if (key == "MemTotal:") {
            total_memory = value;
        } else if (key == "MemAvailable:") {
            free_memory = value;
        }
    }

    if (total_memory > 0) { // Проверка, что total_memory не нулевой
        memoryUsage = ((total_memory - free_memory) / static_cast<double>(total_memory)) * 100;
    } else {
        memoryUsage = 0;
    }
    totalMemory = 100.0; // Полный объем памяти всегда 100%
}

// Функция для получения использования диска и полного объема диска в байтах и преобразование в гигабайты
void getDiskUsage(double& diskUsageGb, double& totalDiskGb) {
    std::ifstream file("/proc/self/mounts");
    std::string line, device, mountpoint, fstype, options;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> device >> mountpoint >> fstype >> options;

        if (mountpoint == "/") {
            // Используем команду 'df' для получения информации о дисковом пространстве
            std::string command = "df --block-size=1 " + mountpoint + " | awk 'NR==2 {print $3, $2}'";
            FILE* pipe = popen(command.c_str(), "r");
            if (pipe) {
                long used_bytes, total_bytes;
                fscanf(pipe, "%ld %ld", &used_bytes, &total_bytes);
                pclose(pipe);

                diskUsageGb = used_bytes / 1024.0 / 1024.0 / 1024.0; // Преобразуем байты в ГБ
                totalDiskGb = total_bytes / 1024.0 / 1024.0 / 1024.0; // Преобразуем байты в ГБ
                return;
            }
        }
    }
}

// Функция для получения имени узла
std::string getNodeName() {
    std::ifstream file("/etc/hostname");
    std::string nodeName;
    std::getline(file, nodeName);
    return nodeName;
}

// Функция для получения MAC-адреса узла
std::string getMacAddress() {
    std::string macAddress;
    std::system("cat /sys/class/net/$(ip route show default | awk '/default/ {print $5}')/address > /tmp/mac_address.txt");
    std::ifstream file("/tmp/mac_address.txt");
    std::getline(file, macAddress);
    std::remove("/tmp/mac_address.txt"); // Удаляем временный файл
    return macAddress;
}

// Функция для получения IP-адреса узла
std::string getNodeIpAddress() {
    std::string ipAddress;
    std::system("hostname -I | awk '{print $1}' > /tmp/ip_address.txt");
    std::ifstream file("/tmp/ip_address.txt");
    std::getline(file, ipAddress);
    std::remove("/tmp/ip_address.txt"); // Удаляем временный файл
    return ipAddress;
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
    ssize_t sentBytes = send(sock, data.c_str(), data.size(), 0);
    if (sentBytes < 0) {
        std::cerr << "Error sending data." << std::endl;
        close(sock);
        return;
    }
    std::cout << "Data sent: " << data << std::endl;

    // Закрываем сокет
    close(sock);
}

int main() {
    std::string serverIp = "192.168.0.3"; // IP-адрес сервера (локальный адрес для тестирования)
    int serverPort = 10900; // Порт сервера

    // Получаем системные метрики
    std::string hostname = getNodeName(); // Имя узла
    std::string macAddress = getMacAddress(); // MAC-адрес узла
    std::string nodeIpAddress = getNodeIpAddress(); // IP-адрес узла

    double cpuUsage, totalCpu;
    getCpuUsage(cpuUsage, totalCpu);

    double memoryUsage, totalMemory;
    getMemoryUsage(memoryUsage, totalMemory);

    double diskUsageGb, totalDiskGb;
    getDiskUsage(diskUsageGb, totalDiskGb);

    std::ostringstream dataStream;
    dataStream << hostname << "," << macAddress << "," << nodeIpAddress<< "," << cpuUsage << "," << totalCpu << "," << memoryUsage << ","
               << totalMemory << "," << diskUsageGb << "," << totalDiskGb;
    std::string data = dataStream.str();

    // Отправляем данные на сервер
    sendDataToServer(serverIp, serverPort, data);

    return 0;
}