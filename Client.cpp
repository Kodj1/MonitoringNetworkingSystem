#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

struct SystemData {
    std::string hostname;
    double cpuUsage;
    struct sysinfo memInfo;
};

std::string getHostname() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return std::string(hostname);
    } else {
        return "unknown";
    }
}

double getCpuUsage() {
    static long prevIdleTime = 0, prevTotalTime = 0;
    long idleTime, totalTime;

    std::ifstream statFile("/proc/stat");
    std::string line;
    std::getline(statFile, line);
    statFile.close();

    std::istringstream ss(line);
    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    idleTime = idle + iowait;
    totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    double cpuUsage = 0.0;
    if (prevTotalTime != 0 && prevIdleTime != 0) {
        long deltaIdle = idleTime - prevIdleTime;
        long deltaTotal = totalTime - prevTotalTime;
        cpuUsage = (1.0 - (double)deltaIdle / deltaTotal) * 100.0;
    }

    prevIdleTime = idleTime;
    prevTotalTime = totalTime;

    return cpuUsage;
}

void sendData(const SystemData& data, const std::string& ipAddress, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address." << std::endl;
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        close(sock);
        return;
    }

    std::ostringstream jsonData;
    jsonData << "{\"hostname\":\"" << data.hostname << "\",";
    jsonData << "\"cpu_usage\": " << data.cpuUsage << ",";
    jsonData << "\"memory\": {\"total\": " << data.memInfo.totalram << ", \"free\": " << data.memInfo.freeram << "}}";

    std::string jsonStr = jsonData.str();

    if (send(sock, jsonStr.c_str(), jsonStr.size(), 0) < 0) {
        std::cerr << "Failed to send data." << std::endl;
    } else {
        std::cout << "Data sent successfully." << std::endl;
    }

    close(sock);
}

int main() {
    std::string serverIp = "127.0.0.1"; // Укажите IP-адрес сервера
    int serverPort = 12345; // Укажите порт сервера

    try {
        while (true) {
            SystemData data;
            data.hostname = getHostname();
            data.cpuUsage = getCpuUsage();
            sysinfo(&data.memInfo);

            sendData(data, serverIp, serverPort);

            std::this_thread::sleep_for(std::chrono::seconds(5)); // Отправка каждые 5 секунд
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
