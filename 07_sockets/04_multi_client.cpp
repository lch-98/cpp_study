/*
 * [Topic] Multi-Client Server — select()로 여러 클라이언트 동시 처리
 * 스레드 없이 하나의 스레드로 여러 클라이언트를 동시에 처리하는 방법.
 * select()는 여러 소켓 중 데이터가 도착한 소켓만 골라준다.
 *
 * select() 동작 원리:
 *   1. fd_set에 감시할 소켓들을 등록
 *   2. select() 호출 → 데이터가 온 소켓이 생길 때까지 대기
 *   3. FD_ISSET()으로 어떤 소켓에 데이터가 왔는지 확인
 *   4. 해당 소켓만 recv() 처리
 *
 * thread vs select:
 *   thread  : 클라이언트마다 스레드 생성 → 간단하지만 많아지면 오버헤드
 *   select  : 단일 스레드로 N개 처리 → 복잡하지만 효율적
 *   (실무에서는 epoll/IOCP 같은 더 발전된 방식 사용)
 *
 * Key points:
 *   - FD_ZERO, FD_SET, FD_ISSET : fd_set 조작 매크로
 *   - timeval : select() 타임아웃 설정
 *   - 서버 소켓도 fd_set에 포함 → 새 연결 감지
 *
 * Practice:
 *   - 한 클라이언트가 보낸 메시지를 모든 클라이언트에 브로드캐스트해보기
 *   - 최대 연결 수 제한 추가해보기
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(12346);  // 12346 포트 사용
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (SOCKADDR*)&addr, sizeof(addr));
    listen(serverSock, SOMAXCONN);
    cout << "[Multi-Client Server] 포트 12346 대기 중 (최대 10 클라이언트)...\n\n";

    vector<SOCKET> clients;  // 연결된 클라이언트 목록

    while (true) {
        // fd_set 구성: 서버 소켓 + 모든 클라이언트 소켓
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(serverSock, &readSet);
        for (SOCKET s : clients) FD_SET(s, &readSet);

        // 100ms 타임아웃으로 select
        timeval timeout = {0, 100000};  // 0초 100000μs = 100ms
        int ready = select(0, &readSet, nullptr, nullptr, &timeout);
        if (ready == SOCKET_ERROR) break;
        if (ready == 0) continue;  // 타임아웃: 아무 이벤트 없음

        // 새 클라이언트 연결 확인
        if (FD_ISSET(serverSock, &readSet)) {
            sockaddr_in clientAddr = {};
            int len = sizeof(clientAddr);
            SOCKET newClient = accept(serverSock, (SOCKADDR*)&clientAddr, &len);
            clients.push_back(newClient);

            char ip[16];
            strcpy_s(ip, inet_ntoa(clientAddr.sin_addr));
            cout << "[연결] " << ip << ":" << ntohs(clientAddr.sin_port)
                 << " (현재 " << clients.size() << "명)\n";

            string welcome = "서버에 접속했습니다. 현재 접속자: "
                           + to_string(clients.size()) + "명\r\n";
            send(newClient, welcome.c_str(), (int)welcome.size(), 0);
        }

        // 각 클라이언트 데이터 확인
        vector<SOCKET> toRemove;
        for (SOCKET s : clients) {
            if (!FD_ISSET(s, &readSet)) continue;

            char buf[1024];
            int len = recv(s, buf, sizeof(buf) - 1, 0);

            if (len <= 0) {
                // 연결 끊김
                cout << "[종료] 클라이언트 연결 끊김\n";
                closesocket(s);
                toRemove.push_back(s);
                continue;
            }

            buf[len] = '\0';
            string msg(buf);
            msg.erase(remove(msg.begin(), msg.end(), '\r'), msg.end());
            msg.erase(remove(msg.begin(), msg.end(), '\n'), msg.end());
            cout << "[수신] " << msg << "\n";

            // 브로드캐스트: 보낸 사람 제외 전체 전송
            string broadcast = "[브로드캐스트] " + msg + "\r\n";
            for (SOCKET other : clients) {
                if (other != s)
                    send(other, broadcast.c_str(), (int)broadcast.size(), 0);
            }

            // 보낸 사람에게 echo
            string echo = "You: " + msg + "\r\n";
            send(s, echo.c_str(), (int)echo.size(), 0);
        }

        // 끊긴 클라이언트 제거
        for (SOCKET s : toRemove)
            clients.erase(remove(clients.begin(), clients.end(), s), clients.end());
    }

    for (SOCKET s : clients) closesocket(s);
    closesocket(serverSock);
    WSACleanup();
    return 0;
}
