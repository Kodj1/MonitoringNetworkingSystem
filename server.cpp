#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <libpq-fe.h>

// Функция для вставки данных в таблицу nodes
void insertNodeIfNotExists(PGconn* conn, int nodeId, const std::string& nodeName, const std::string& nodeIpAddress) {
    std::ostringstream checkQuery;
    checkQuery << "SELECT 1 FROM nodes WHERE id = " << nodeId << ";";
    PGresult* res = PQexec(conn, checkQuery.str().c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Check node existence failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return;
    }

    if (PQntuples(res) == 0) {
        // Node does not exist, insert it with required fields
        std::ostringstream insertQuery;
        insertQuery << "INSERT INTO nodes (id, name, ip_address) VALUES (" << nodeId << ", '" << nodeName << "', '" << nodeIpAddress << "');";
        PGresult* insertRes = PQexec(conn, insertQuery.str().c_str());

        if (PQresultStatus(insertRes) != PGRES_COMMAND_OK) {
            std::cerr << "Insert node failed: " << PQerrorMessage(conn) << std::endl;
        }

        PQclear(insertRes);
    }

    PQclear(res);
}

// Функция для вставки данных в базу данных PostgreSQL
void insertToDatabase(int nodeId, const std::string& nodeName, const std::string& nodeIpAddress, double cpuUsage, double memoryUsage, double networkIn, double networkOut) {
    const char* conninfo = "host=localhost dbname=mns user=postgres password=12345";
    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return;
    }

    // Проверка и вставка узла, если он не существует
    insertNodeIfNotExists(conn, nodeId, nodeName, nodeIpAddress);

    std::ostringstream query;
    query << "INSERT INTO metrics (node_id, cpu_usage, memory_usage, network_in, network_out) VALUES ("
          << nodeId << ", " << cpuUsage << ", " << memoryUsage << ", " << networkIn << ", " << networkOut << ");";

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

    // Парсим полученные данные (предполагаем, что данные получены в формате: nodeId,cpuUsage,memoryUsage,networkIn,networkOut)
    int nodeId;
    double cpuUsage, memoryUsage, networkIn, networkOut;
    char delimiter;

    std::istringstream iss(buffer);
    if (!(iss >> nodeId >> delimiter >> cpuUsage >> delimiter >> memoryUsage >> delimiter >> networkIn >> delimiter >> networkOut)) {
        std::cerr << "Error parsing data." << std::endl;
        close(clientSocket);
        return;
    }

    // Заменить эти значения фактическими значениями для nodeName и nodeIpAddress
    std::string nodeName = "defaultNodeName";
    std::string nodeIpAddress = "127.0.0.1";

    // Сохраняем данные в базу данных
    insertToDatabase(nodeId, nodeName, nodeIpAddress, cpuUsage, memoryUsage, networkIn, networkOut);

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