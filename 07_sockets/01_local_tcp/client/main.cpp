/*
 * [Topic] Local TCP Client (Winsock)
 * Windows Winsock2를 사용해 로컬 TCP 클라이언트를 구현하는 예제.
 *
 * 클라이언트 흐름:
 *   1. WSAStartup  : Winsock 라이브러리 초기화
 *   2. socket()    : 클라이언트 소켓 생성
 *   3. connect()   : 서버(127.0.0.1:12345)에 연결 요청
 *   4. send()      : 서버로 메시지 전송
 *   5. recv()      : 서버 응답 수신
 *   6. closesocket / WSACleanup : 정리
 *
 * 실행 방법: server/main.cpp를 먼저 실행한 후 이 클라이언트를 실행
 * 빌드: CMakeLists.txt 참고
 */
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
