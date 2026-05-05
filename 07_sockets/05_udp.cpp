/*
 * [Topic] UDP Socket — 비연결형 소켓
 * TCP와 달리 연결 수립(3-way handshake) 없이 바로 데이터를 전송한다.
 * 게임 서버, 실시간 스트리밍, DNS 등에서 사용.
 *
 * TCP vs UDP:
 *   TCP : 연결 지향, 순서 보장, 손실 재전송, 느림
 *   UDP : 비연결, 순서 미보장, 손실 허용, 빠름
 *
 * UDP 핵심 함수:
 *   sendto(sock, data, len, 0, addr, addrLen)  : 주소 지정해서 전송
 *   recvfrom(sock, buf, len, 0, &addr, &len)   : 송신자 주소도 함께 수신
 *
 * Key points:
 *   - connect() 없이 바로 sendto()
 *   - 하나의 소켓으로 서버/클라이언트 역할 동시 가능
 *   - 데이터그램 단위 전송 (패킷 경계 유지)
 *
 * 이 파일은 서버+클라이언트를 하나로 합친 핑퐁 예제:
 *   - 두 터미널에서 각각 실행 (포트를 서로 교환)
 *   - 터미널 A: 로컬 9001, 상대 9002
 *   - 터미널 B: 로컬 9002, 상대 9001
 *
 * Practice:
 *   - UDP로 간단한 시간 동기화 프로토콜 구현해보기
 *   - 패킷 손실 시뮬레이션 (rand()로 일정 확률로 수신 무시)
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

atomic<bool> running{true};

// 수신 스레드 (백그라운드)
void receiveLoop(SOCKET sock) {
    char buf[1024];
    sockaddr_in senderAddr = {};
    int senderLen = sizeof(senderAddr);

    while (running) {
        // 타임아웃 설정 (1초마다 running 체크)
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(sock, &readSet);
        timeval tv = {1, 0};

        if (select(0, &readSet, nullptr, nullptr, &tv) <= 0) continue;

        int len = recvfrom(sock, buf, sizeof(buf) - 1, 0,
                           (SOCKADDR*)&senderAddr, &senderLen);
        if (len <= 0) continue;

        buf[len] = '\0';
        cout << "\n[수신] " << inet_ntoa(senderAddr.sin_addr)
             << ":" << ntohs(senderAddr.sin_port) << " → " << buf << "\n> ";
        cout.flush();
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 로컬 포트와 상대 포트 입력
    int localPort, remotePort;
    cout << "내 포트 (예: 9001): "; cin >> localPort;
    cout << "상대 포트 (예: 9002): "; cin >> remotePort;
    cin.ignore();

    // UDP 소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // 내 포트에 바인딩
    sockaddr_in myAddr = {};
    myAddr.sin_family      = AF_INET;
    myAddr.sin_port        = htons(localPort);
    myAddr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (SOCKADDR*)&myAddr, sizeof(myAddr));

    // 상대방 주소 설정
    sockaddr_in remoteAddr = {};
    remoteAddr.sin_family      = AF_INET;
    remoteAddr.sin_port        = htons(remotePort);
    remoteAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    cout << "\n[UDP 시작] 로컬:" << localPort << " ↔ 상대:" << remotePort << "\n";
    cout << "메시지 입력 (quit 종료):\n> ";

    // 수신 스레드 시작
    thread recvThread(receiveLoop, sock);

    // 송신 루프
    string msg;
    while (getline(cin, msg)) {
        if (msg == "quit") break;
        sendto(sock, msg.c_str(), (int)msg.size(), 0,
               (SOCKADDR*)&remoteAddr, sizeof(remoteAddr));
        cout << "> ";
    }

    running = false;
    recvThread.join();

    closesocket(sock);
    WSACleanup();
    return 0;
}
