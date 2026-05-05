# 07. Sockets (소켓 통신)

Winsock2로 TCP/UDP 소켓 통신을 구현한다. 외부 라이브러리 없이 Windows SDK만으로 빌드 가능.

---

## 학습 순서

| 파일 | 주제 | 핵심 개념 |
|------|------|---------|
| [01_local_tcp/](01_local_tcp/) | 기본 TCP 서버/클라이언트 | `socket`, `bind`, `listen`, `accept`, `connect` |
| [02_http_raw.cpp](02_http_raw.cpp) | Raw HTTP GET 구현 | `getaddrinfo`, HTTP/1.1 요청 구조, 헤더/바디 파싱 |
| [03_echo_server.cpp](03_echo_server.cpp) | Echo 서버 (반복 수신) | `SO_REUSEADDR`, recv 루프, 연결 종료 감지 |
| [04_multi_client.cpp](04_multi_client.cpp) | select()로 다중 클라이언트 | `fd_set`, `FD_SET`, `select`, 브로드캐스트 |
| [05_udp.cpp](05_udp.cpp) | UDP 핑퐁 통신 | `SOCK_DGRAM`, `sendto`, `recvfrom`, 비연결형 |
| [06_threaded_server.cpp](06_threaded_server.cpp) | 스레드 기반 다중 클라이언트 | `thread::detach`, `mutex`, `atomic` |

---

## 빌드 (모든 파일에 ws2_32.lib 필요)

```cmd
cl /std:c++17 /EHsc 02_http_raw.cpp /link ws2_32.lib
cl /std:c++17 /EHsc 03_echo_server.cpp /link ws2_32.lib
cl /std:c++17 /EHsc 04_multi_client.cpp /link ws2_32.lib
cl /std:c++17 /EHsc 05_udp.cpp /link ws2_32.lib
cl /std:c++17 /EHsc 06_threaded_server.cpp /link ws2_32.lib
```

---

## TCP 서버 흐름

```
[Server]                    [Client]
socket()                    socket()
bind()
listen()
accept() ←── connect() ────
recv()   ←── send()    ────  데이터 전송
send()   ───→ recv()         응답 수신
closesocket()               closesocket()
```

## select() vs thread 방식 비교

| | select() | thread per client |
|-|----------|-------------------|
| 스레드 수 | 1개 | 클라이언트 수만큼 |
| 구현 난이도 | 복잡 | 직관적 |
| 클라이언트 수 제한 | FD_SETSIZE(64) | 메모리/OS 제한 |
| 실무 발전형 | epoll(Linux) | thread pool |

## 실행 순서

**01_local_tcp:**
```
터미널 1: server.exe  (먼저 실행)
터미널 2: client.exe  (나중 실행)
```

**03_echo_server + telnet:**
```
터미널 1: 03_echo_server.exe
터미널 2: telnet 127.0.0.1 12345
```

**05_udp (두 터미널):**
```
터미널 1: 05_udp.exe → 내 포트: 9001, 상대: 9002
터미널 2: 05_udp.exe → 내 포트: 9002, 상대: 9001
```

> **앞 단계:** [06_multithreading](../06_multithreading/)  
> **다음 단계:** [08_console_ui](../08_console_ui/)
