#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <libpq-fe.h>
#include <ctime>
#include <vector>
#include <fstream>

// Function to log failed insertions into a text file
void logFailedInsertToFile(const std::string& hostname, const std::string& macAddress, const std::string& ipAddress, 
                           double cpuUsage, double totalCpu, double memoryUsage, double totalMemory, 
                           double diskUsageGb, double totalDiskGb, const std::string& errorMessage) {
    std::ofstream file("failed_inserts.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }
    
    // Get the current timestamp
    std::time_t now = std::time(nullptr);
    char collectedAt[100];
    std::strftime(collectedAt, sizeof(collectedAt), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    // Write the data and error message to the file
    file << "Timestamp: " << collectedAt << std::endl;
    file << "Hostname: " << hostname << std::endl;
    file << "MAC Address: " << macAddress << std::endl;
    file << "IP Address: " << ipAddress << std::endl;
    file << "CPU Usage: " << cpuUsage << std::endl;
    file << "Total CPU: " << totalCpu << std::endl;
    file << "Memory Usage: " << memoryUsage << std::endl;
    file << "Total Memory: " << totalMemory << std::endl;
    file << "Disk Usage GB: " << diskUsageGb << std::endl;
    file << "Total Disk GB: " << totalDiskGb << std::endl;
    file << "Error Message: " << errorMessage << std::endl;
    file << "----------------------------------------" << std::endl;

    std::cout << "Insertion error logged to file successfully." << std::endl;
    
    file.close();
}

// Function to insert data into the PostgreSQL database
void insertToDatabase(const std::string& hostname, const std::string& macAddress, const std::string& ipAddress, 
                      double cpuUsage, double totalCpu, double memoryUsage, double totalMemory, 
                      double diskUsageGb, double totalDiskGb) {
    const char* conninfo = "host=localhost dbname=mns user=postgres password=12345"; // Database connection configuration
    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::string errorMessage = "Connection to database failed: " + std::string(PQerrorMessage(conn));
        std::cerr << errorMessage << std::endl;
        PQfinish(conn);
        logFailedInsertToFile(hostname, macAddress, ipAddress, cpuUsage, totalCpu, memoryUsage, totalMemory, diskUsageGb, totalDiskGb, errorMessage);
        return;
    }

    // Data validation before insertion
    if (cpuUsage < 0 || cpuUsage > 100 ||
        totalCpu < 0 || totalCpu > 100 ||
        memoryUsage < 0 || memoryUsage > 100 ||
        totalMemory < 0 || totalMemory > 100 ||
        diskUsageGb < 0 || diskUsageGb > 1e15 ||
        totalDiskGb < 0 || totalDiskGb > 1e15) {
        std::string errorMessage = "Data validation failed: one or more values are out of accepted range.";
        std::cerr << errorMessage << std::endl;
        PQfinish(conn);
        logFailedInsertToFile(hostname, macAddress, ipAddress, cpuUsage, totalCpu, memoryUsage, totalMemory, diskUsageGb, totalDiskGb, errorMessage);
        return;
    }

    // Get the current timestamp
    std::time_t now = std::time(nullptr);
    char collectedAt[100];
    std::strftime(collectedAt, sizeof(collectedAt), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Forming the SQL query
    std::ostringstream query;
    query << "INSERT INTO metrics (hostname, mac_address, ip_address, cpu_usage, total_cpu, memory_usage, total_memory, "
          << "disk_usage_gb, total_disk_gb, collected_at) VALUES ('"
          << hostname << "', '" << macAddress << "', '" << ipAddress << "', " << cpuUsage << ", " << totalCpu << ", " 
          << memoryUsage << ", " << totalMemory << ", " << diskUsageGb << ", " << totalDiskGb << ", '" << collectedAt << "');";

    // Executing the SQL query
    PGresult* res = PQexec(conn, query.str().c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string errorMessage = "Insert failed: " + std::string(PQerrorMessage(conn));
        std::cerr << errorMessage << std::endl;
        PQclear(res);
        PQfinish(conn);
        logFailedInsertToFile(hostname, macAddress, ipAddress, cpuUsage, totalCpu, memoryUsage, totalMemory, diskUsageGb, totalDiskGb, errorMessage);
        return;
    }

    std::cout << "Data inserted into database successfully." << std::endl;

    PQclear(res);
    PQfinish(conn);
}

// Function to split a string by a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(str);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to handle the client connection
void handleClient(int clientSocket) {
    const size_t bufferSize = 1024;
    char buffer[bufferSize];

    // Waiting for data from the client
    ssize_t bytesRead = recv(clientSocket, buffer, bufferSize - 1, 0);
    if (bytesRead < 0) {
        std::cerr << "Error reading from socket." << std::endl;
        close(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the string
    std::cout << "Received data: " << buffer << std::endl;

    std::string data(buffer);
    std::vector<std::string> tokens = splitString(data, ',');

    if (tokens.size() != 9) {
        std::cerr << "Error parsing data: incorrect number of tokens." << std::endl;
        close(clientSocket);
        return;
    }

    std::string hostname = tokens[0];
    std::string macAddress = tokens[1];
    std::string ipAddress = tokens[2];
    double cpuUsage = std::stod(tokens[3]);
    double totalCpu = std::stod(tokens[4]);
    double memoryUsage = std::stod(tokens[5]);
    double totalMemory = std::stod(tokens[6]);
    double diskUsageGb = std::stod(tokens[7]);
    double totalDiskGb = std::stod(tokens[8]);

    // Debug prints
    std::cout << "Parsed Data:" << std::endl;
    std::cout << "Hostname: " << hostname << std::endl;
    std::cout << "MAC Address: " << macAddress << std::endl;
    std::cout << "IP Address: " << ipAddress << std::endl;
    std::cout << "CPU Usage: " << cpuUsage << std::endl;
    std::cout << "Total CPU: " << totalCpu << std::endl;
    std::cout << "Memory Usage: " << memoryUsage << std::endl;
    std::cout << "Total Memory: " << totalMemory << std::endl;
    std::cout << "Disk Usage GB: " << diskUsageGb << std::endl;
    std::cout << "Total Disk GB: " << totalDiskGb << std::endl;

    // Save data to the database
    insertToDatabase(hostname, macAddress, ipAddress, cpuUsage, totalCpu, memoryUsage, totalMemory, diskUsageGb, totalDiskGb);

    close(clientSocket);
    std::cout << "Client disconnected." << std::endl;
}

int main() {
    const int port = 10900; // Server port

    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    // Configure address and port
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind socket to address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port " << port << "..." << std::endl;

    while (true) {
        // Accept incoming connection
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }

        std::cout << "Client connected." << std::endl;

        // Handle client in a separate function
        handleClient(clientSocket);
    }

    close(serverSocket);
    return 0;
}