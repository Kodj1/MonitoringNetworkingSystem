#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>

// Функция для получения использования CPU и полного объема CPU
void getCpuUsage(double& cpuUsage, double& totalCpu) {
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

        cpuUsage = usage;
        totalCpu = 100.0; // Полный объем CPU всегда 100%
    }
}

// Функция для получения использования памяти и полного объема памяти
void getMemoryUsage(double& memoryUsage, double& totalMemory) {
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

    memoryUsage = ((total_memory - free_memory) / static_cast<double>(total_memory)) * 100;
    totalMemory = 100.0; // Полный объем памяти всегда 100%
}

// Функция для получения сетевого трафика и полного объема сетевого трафика
void getNetworkUsage(double& networkInMbps, double& totalNetworkInMbps, double& networkOutMbps, double& totalNetworkOutMbps) {
    std::ifstream file("/proc/net/dev");
    std::string line, iface;
    long rx_bytes, tx_bytes;
    static long prev_rx_bytes, prev_tx_bytes;

    // Пропускаем первые две строки заголовков
    std::getline(file, line);
    std::getline(file, line);

    networkInMbps = 0;
    networkOutMbps = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> iface >> rx_bytes;
        ss.ignore(64, ' '); // Пропускаем ненужные поля
        ss >> tx_bytes;

        if (iface != "lo:") { // Игнорируем loopback интерфейс
            networkInMbps += rx_bytes / 125000.0; // Преобразуем байты в Мбит/с
            networkOutMbps += tx_bytes / 125000.0; // Преобразуем байты в Мбит/с
        }
    }

    networkInMbps -= prev_rx_bytes / 125000.0;
    networkOutMbps -= prev_tx_bytes / 125000.0;

    prev_rx_bytes += networkInMbps * 125000;
    prev_tx_bytes += networkOutMbps * 125000;

    totalNetworkInMbps = networkInMbps;
    totalNetworkOutMbps = networkOutMbps;
}

// Функция для получения использования диска и полного объема диска в байтах и преобразование в гигабайты
void getDiskUsage(double& diskUsageGb, double& totalDiskGb) {
    std::ifstream file("/proc/self/mounts");
    std::string line, device, mountpoint, fstype, options;
    long blocks, used, available;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> device >> mountpoint >> fstype >> options;

        if (mountpoint == "/") {
            std::ifstream statFile("/proc/self/mountstats");
            while (std::getline(statFile, line)) {
                if (line.find("device " + device + " mounted on /") != std::string::npos) {
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
    }
}

// Функция для получения имени узла
std::string getNodeName() {
    std::ifstream file("/etc/hostname");
    std::string nodeName;
    std::getline(file, nodeName);
    return nodeName;
}

// Функция для получения IP-адреса узла
std::string getNodeIpAddress() {
    std::string ipAddress;
    std::system("hostname -I | awk '{print $1}' > /tmp/ip_address.txt");
    std::ifstream file("/tmp/ip_address.txt");
    std::getline(file, ipAddress);
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
    send(sock, data.c_str(), data.size(), 0);
    std::cout << "Data sent: " << data << std::endl;

    // Закрываем сокет
    close(sock);
}

int main() {
    std::string serverIp = "192.168.0.3"; // IP-адрес сервера
    int serverPort = 8080; // Порт сервера

    // Получаем системные метрики
    std::string hostname = getNodeName(); // Имя узла
    std::string nodeIpAddress = getNodeIpAddress(); // IP-адрес узла

    double cpuUsage, totalCpu;
    getCpuUsage(cpuUsage, totalCpu);

    double memoryUsage, totalMemory;
    getMemoryUsage(memoryUsage, totalMemory);

    double networkInMbps, totalNetworkInMbps, networkOutMbps, totalNetworkOutMbps;
    getNetworkUsage(networkInMbps, totalNetworkInMbps, networkOutMbps, totalNetworkOutMbps);

    double diskUsageGb, totalDiskGb;
    getDiskUsage(diskUsageGb, totalDiskGb);

    // Формируем строку данных в формате hostname,cpuUsage,totalCpu,memoryUsage,totalMemory,networkInMbps,totalNetworkInMbps,networkOutMbps,totalNetworkOutMbps,diskUsageGb,totalDiskGb
    std::ostringstream dataStream;
    dataStream << hostname << "," << cpuUsage << "," << totalCpu << "," << memoryUsage << "," << totalMemory << ","
               << networkInMbps << "," << totalNetworkInMbps << "," << networkOutMbps << "," << totalNetworkOutMbps << ","
               << diskUsageGb << "," << totalDiskGb;
    std::string data = dataStream.str();

    // Отправляем данные на сервер
    sendDataToServer(serverIp, serverPort, data);

    return 0;
}