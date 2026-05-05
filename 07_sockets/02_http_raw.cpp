/*
 * [Topic] Raw HTTP GET — 라이브러리 없이 HTTP 직접 구현
 * libcurl 없이 Winsock TCP 소켓으로 HTTP/1.1 요청을 직접 만들어 보낸다.
 * HTTP가 결국 TCP 위에서 텍스트를 주고받는 프로토콜임을 이해한다.
 *
 * HTTP/1.1 요청 구조:
 *   GET /경로 HTTP/1.1\r\n
 *   Host: 호스트명\r\n
 *   Connection: close\r\n
 *   \r\n                  ← 헤더 끝을 빈 줄로 표시
 *
 * HTTP 응답 구조:
 *   HTTP/1.1 200 OK\r\n
 *   Content-Type: text/html\r\n
 *   \r\n
 *   <실제 바디>
 *
 * Key points:
 *   - getaddrinfo() : 도메인 → IP 주소 변환 (DNS 조회)
 *   - 포트 80 : HTTP 기본 포트
 *   - \r\n : HTTP 헤더 구분자 (LF만으로는 안 됨)
 *   - recv() 루프 : 응답이 여러 번에 나뉘어 올 수 있음
 *
 * Practice:
 *   - 다른 경로(예: /about)로 요청해보기
 *   - 응답 헤더와 바디를 분리해서 출력하기
 *   - POST 요청 구현해보기 (Content-Length 헤더 필요)
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

// HTTP GET 요청 문자열 생성
string buildRequest(const string& host, const string& path) {
    return "GET " + path + " HTTP/1.1\r\n"
           "Host: " + host + "\r\n"
           "User-Agent: cpp-raw-socket/1.0\r\n"
           "Accept: */*\r\n"
           "Connection: close\r\n"
           "\r\n";
}

// 응답에서 헤더/바디 분리
void parseResponse(const string& response) {
    size_t headerEnd = response.find("\r\n\r\n");
    if (headerEnd == string::npos) {
        cout << response;
        return;
    }
    string headers = response.substr(0, headerEnd);
    string body    = response.substr(headerEnd + 4);

    cout << "=== 응답 헤더 ===\n" << headers << "\n\n";
    cout << "=== 응답 바디 (앞 500자) ===\n"
         << body.substr(0, min((size_t)500, body.size())) << "\n";
    cout << "\n[바디 총 " << body.size() << " bytes]\n";
}

int main() {
    // Winsock 초기화
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    const string host = "example.com";
    const string path = "/";
    const string port = "80";

    // DNS 조회 (도메인 → IP)
    addrinfo hints = {}, *result;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    cout << host << " DNS 조회 중...\n";
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &result) != 0) {
        cerr << "DNS 조회 실패\n";
        WSACleanup();
        return 1;
    }

    // 소켓 생성 및 연결
    SOCKET sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connect(sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        cerr << "연결 실패\n";
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);
    cout << "연결 성공 (port 80)\n\n";

    // HTTP 요청 전송
    string request = buildRequest(host, path);
    cout << "=== 전송한 요청 ===\n" << request;
    send(sock, request.c_str(), (int)request.size(), 0);

    // 응답 수신 (여러 번 recv 필요)
    string response;
    char buf[4096];
    int received;
    while ((received = recv(sock, buf, sizeof(buf) - 1, 0)) > 0) {
        buf[received] = '\0';
        response += buf;
    }

    closesocket(sock);
    WSACleanup();

    parseResponse(response);
    return 0;
}
