/*
 * [Topic] Echo Server — 받은 메시지를 그대로 돌려보내는 서버
 * 01_local_tcp의 1회성 1:1 서버를 개선해 반복 수신이 가능한 서버로 만든다.
 * telnet이나 직접 만든 클라이언트로 테스트 가능.
 *
 * 01_local_tcp와의 차이:
 *   - while 루프로 메시지를 계속 수신
 *   - 받은 내용을 그대로 echo (반향)
 *   - 클라이언트가 "quit" 전송 시 연결 종료
 *   - 다음 클라이언트 연속 수락 가능
 *
 * Key points:
 *   - recv() 반환값 0 : 클라이언트가 연결 종료
 *   - recv() 반환값 -1 : 오류
 *   - SO_REUSEADDR : 서버 재시작 시 "address already in use" 방지
 *
 * 실행 방법:
 *   1. 이 서버 실행
 *   2. 새 터미널에서: telnet 127.0.0.1 12345
 *      또는 04_multi_client.cpp 클라이언트 실행
 *
 * Practice:
 *   - 받은 메시지를 대문자로 변환해서 돌려보내기
 *   - 접속 시간과 메시지 수를 로그로 출력하기
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);

    // SO_REUSEADDR: 서버 재시작 시 포트 즉시 재사용
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (SOCKADDR*)&addr, sizeof(addr));
    listen(serverSock, SOMAXCONN);
    cout << "[Echo Server] 포트 12345에서 대기 중...\n";
    cout << "  telnet 127.0.0.1 12345 로 접속, quit 입력 시 종료\n\n";

    while (true) {
        sockaddr_in clientAddr = {};
        int addrLen = sizeof(clientAddr);
        SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &addrLen);

        char clientIP[16];
        strcpy_s(clientIP, inet_ntoa(clientAddr.sin_addr));
        cout << "[연결] " << clientIP << ":" << ntohs(clientAddr.sin_port) << "\n";

        // 환영 메시지 전송
        string welcome = "Echo Server에 오신 것을 환영합니다. 'quit' 입력 시 종료.\r\n";
        send(clientSock, welcome.c_str(), (int)welcome.size(), 0);

        // 에코 루프
        char buf[1024];
        int msgCount = 0;
        while (true) {
            int len = recv(clientSock, buf, sizeof(buf) - 1, 0);
            if (len <= 0) break;  // 연결 종료 또는 오류

            buf[len] = '\0';
            string msg(buf);

            // 줄바꿈 제거
            msg.erase(remove(msg.begin(), msg.end(), '\r'), msg.end());
            msg.erase(remove(msg.begin(), msg.end(), '\n'), msg.end());

            cout << "  수신 [" << ++msgCount << "]: " << msg << "\n";

            if (msg == "quit") {
                string bye = "안녕히 가세요!\r\n";
                send(clientSock, bye.c_str(), (int)bye.size(), 0);
                break;
            }

            // Echo: 그대로 돌려보내기
            string reply = "Echo: " + msg + "\r\n";
            send(clientSock, reply.c_str(), (int)reply.size(), 0);
        }

        closesocket(clientSock);
        cout << "[종료] 클라이언트 연결 끊김 (메시지 " << msgCount << "개)\n\n";
    }

    closesocket(serverSock);
    WSACleanup();
    return 0;
}
