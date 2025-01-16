#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <libpq-fe.h>

// Функция для вставки данных в базу данных PostgreSQL
void insertToDatabase(const std::string& hostname, double cpuUsage, double totalCpu, double memoryUsage, double totalMemory, 
                      double networkInMbps, double totalNetworkInMbps, double networkOutMbps, double totalNetworkOutMbps, 
                      double diskUsageGb, double totalDiskGb) {
    const char* conninfo = "host=localhost dbname=mns user=postgres password=12345";
    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return;
    }

    std::ostringstream query;
    query << "INSERT INTO metrics (hostname, cpu_usage, total_cpu, memory_usage, total_memory, "
          << "network_in_mbps, total_network_in_mbps, network_out_mbps, total_network_out_mbps, "
          << "disk_usage_gb, total_disk_gb) VALUES ('"
          << hostname << "', " << cpuUsage << ", " << totalCpu << ", " << memoryUsage << ", " << totalMemory << ", "
          << networkInMbps << ", " << totalNetworkInMbps << ", " << networkOutMbps << ", " << totalNetworkOutMbps << ", "
          << diskUsageGb << ", " << totalDiskGb << ");";

    PGresult* res = PQexec(conn, query.str().c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfinish(conn);
        return;
    }

    std::cout << "Data inserted into database successfully." << std::endl;

    PQclear(res);
    PQfinish(conn);
}

// Функция для обработки клиента
void handleClient(int clientSocket) {
    const size_t bufferSize = 1024;
    char buffer[bufferSize];

    // Ожидание данных от клиента
    ssize_t bytesRead = recv(clientSocket, buffer, bufferSize - 1, 0);
    if (bytesRead < 0) {
        std::cerr << "Error reading from socket." << std::endl;
        close(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0'; // Завершаем строку
    std::cout << "Received data: " << buffer << std::endl;

    // Парсим полученные данные (предполагаем, что данные получены в формате: hostname,cpuUsage,totalCpu,memoryUsage,totalMemory,networkInMbps,totalNetworkInMbps,networkOutMbps,totalNetworkOutMbps,diskUsageGb,totalDiskGb)
    std::string hostname;
    double cpuUsage, totalCpu, memoryUsage, totalMemory, networkInMbps, totalNetworkInMbps, networkOutMbps, totalNetworkOutMbps, diskUsageGb, totalDiskGb;
    char delimiter;

    std::istringstream iss(buffer);
    if (!(std::getline(iss, hostname, ',') >> cpuUsage >> delimiter >> totalCpu >> delimiter >> memoryUsage >> delimiter >> totalMemory >> delimiter
          >> networkInMbps >> delimiter >> totalNetworkInMbps >> delimiter >> networkOutMbps >> delimiter >> totalNetworkOutMbps >> delimiter
          >> diskUsageGb >> delimiter >> totalDiskGb)) {
        std::cerr << "Error parsing data." << std::endl;
        close(clientSocket);
        return;
    }

    // Сохраняем данные в базу данных
    insertToDatabase(hostname, cpuUsage, totalCpu, memoryUsage, totalMemory, networkInMbps, totalNetworkInMbps, networkOutMbps, totalNetworkOutMbps, diskUsageGb, totalDiskGb);

    close(clientSocket);
    std::cout << "Client disconnected." << std::endl;
}

int main() {
    const int port = 8080; // Укажите порт сервера

    // Создаем сокет
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    // Настраиваем адрес и порт
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Привязываем сокет к адресу и порту
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    // Слушаем входящие подключения
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port " << port << "..." << std::endl;

    while (true) {
        // Принимаем входящее подключение
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }

        std::cout << "Client connected." << std::endl;

        // Обрабатываем клиента в отдельной функции
        handleClient(clientSocket);
    }

    close(serverSocket);
    return 0;
}