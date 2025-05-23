#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);
    std::cout << "서버 실행 중. 클라이언트 기다리는 중...\n";

    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    std::cout << "클라이언트 접속됨!\n";

    char buffer[1024] = {};
    int recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recvLen > 0) {
        std::cout << "클라이언트로부터 메시지: " << buffer << "\n";
        send(clientSocket, "Hello from Server!", 19, 0);
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
