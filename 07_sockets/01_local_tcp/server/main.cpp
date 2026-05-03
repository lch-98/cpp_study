/*
 * [Topic] Local TCP Server (Winsock)
 * Windows Winsock2를 사용해 로컬 TCP 서버를 구현하는 예제.
 *
 * 서버 흐름:
 *   1. WSAStartup  : Winsock 라이브러리 초기화
 *   2. socket()    : 서버 소켓 생성 (TCP = SOCK_STREAM)
 *   3. bind()      : 소켓에 IP/포트(12345) 바인딩
 *   4. listen()    : 연결 요청 대기
 *   5. accept()    : 클라이언트 연결 수락 → 새 소켓 반환
 *   6. recv()      : 클라이언트 메시지 수신
 *   7. send()      : 클라이언트에 응답 전송
 *   8. closesocket / WSACleanup : 정리
 *
 * 실행 방법: 서버를 먼저 실행한 후 client를 실행
 * 빌드: CMakeLists.txt 참고
 */
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
