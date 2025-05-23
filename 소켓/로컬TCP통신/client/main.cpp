#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    send(clientSocket, "Hello from Client!", 19, 0);

    char buffer[1024] = {};
    int recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recvLen > 0) {
        std::cout << "서버로부터 메시지: " << buffer << "\n";
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
