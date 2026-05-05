/*
 * [Topic] Threaded Server — 클라이언트마다 스레드를 생성하는 서버
 * 04_multi_client.cpp의 select() 방식과 대비되는 멀티스레드 방식.
 * 실무에서 가장 직관적이고 많이 쓰이는 패턴.
 *
 * 구조:
 *   메인 스레드  : accept() 루프로 새 연결 대기
 *   워커 스레드  : 클라이언트 1개 전담, 연결 종료 시 스레드도 종료
 *
 * select vs thread 방식:
 *   select   : 단일 스레드, 소켓 수 제한(FD_SETSIZE=64), 구현 복잡
 *   thread   : 직관적, 클라이언트 수만큼 스레드 생성 (많으면 오버헤드)
 *   실무 대안 : thread pool + queue (18_advanced_threading 참고)
 *
 * Key points:
 *   - detach() : 스레드가 독립적으로 실행, 완료 시 자동 정리
 *   - mutex로 cout 보호 (멀티스레드에서 cout은 스레드 안전하지 않음)
 *   - 공유 자원(clients 카운터)은 atomic으로 보호
 *
 * 실행 방법:
 *   1. 이 서버 실행
 *   2. 여러 터미널에서 동시에: telnet 127.0.0.1 12347
 *
 * Practice:
 *   - 최대 클라이언트 수 제한 추가 (atomic<int>로 카운팅)
 *   - 각 클라이언트에 고유 ID 부여해서 로그 출력
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

mutex coutMtx;
atomic<int> clientCount{0};
atomic<int> nextId{1};

// 클라이언트 핸들러 (각 스레드에서 실행)
void handleClient(SOCKET clientSock, string clientIP, int port, int id) {
    ++clientCount;
    {
        lock_guard<mutex> lock(coutMtx);
        cout << "[연결 #" << id << "] " << clientIP << ":" << port
             << " (총 " << clientCount.load() << "명)\n";
    }

    string welcome = "안녕하세요! 당신은 클라이언트 #" + to_string(id) + " 입니다.\r\n"
                     "현재 접속자: " + to_string(clientCount.load()) + "명\r\n";
    send(clientSock, welcome.c_str(), (int)welcome.size(), 0);

    char buf[1024];
    int msgCount = 0;
    while (true) {
        int len = recv(clientSock, buf, sizeof(buf) - 1, 0);
        if (len <= 0) break;

        buf[len] = '\0';
        string msg(buf);
        msg.erase(remove(msg.begin(), msg.end(), '\r'), msg.end());
        msg.erase(remove(msg.begin(), msg.end(), '\n'), msg.end());
        ++msgCount;

        {
            lock_guard<mutex> lock(coutMtx);
            cout << "[#" << id << " 수신] " << msg << "\n";
        }

        if (msg == "quit") {
            string bye = "안녕히 가세요!\r\n";
            send(clientSock, bye.c_str(), (int)bye.size(), 0);
            break;
        }

        string reply = "[#" + to_string(id) + " Echo] " + msg + "\r\n";
        send(clientSock, reply.c_str(), (int)reply.size(), 0);
    }

    closesocket(clientSock);
    --clientCount;
    {
        lock_guard<mutex> lock(coutMtx);
        cout << "[종료 #" << id << "] 메시지 " << msgCount
             << "개, 남은 접속자: " << clientCount.load() << "명\n";
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(12347);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (SOCKADDR*)&addr, sizeof(addr));
    listen(serverSock, SOMAXCONN);
    cout << "[Threaded Server] 포트 12347 대기 중...\n";
    cout << "  telnet 127.0.0.1 12347 로 여러 터미널에서 동시 접속해보세요\n\n";

    while (true) {
        sockaddr_in clientAddr = {};
        int addrLen = sizeof(clientAddr);
        SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &addrLen);
        if (clientSock == INVALID_SOCKET) break;

        // 클라이언트마다 새 스레드 생성 후 detach
        string ip = inet_ntoa(clientAddr.sin_addr);
        int port  = ntohs(clientAddr.sin_port);
        int id    = nextId++;

        thread(handleClient, clientSock, ip, port, id).detach();
    }

    closesocket(serverSock);
    WSACleanup();
    return 0;
}
