# 07. Sockets & HTTP (소켓 통신)

TCP 소켓으로 로컬 서버-클라이언트 통신을 구현하고,
HTTP 라이브러리(libcurl)로 외부 API를 호출합니다.

---

## 학습 순서

### [01_local_tcp](01_local_tcp/) — 로컬 TCP 통신
| 파일 | 설명 |
|------|------|
| [server/main.cpp](01_local_tcp/server/main.cpp) | Winsock TCP 서버: bind → listen → accept → recv/send |
| [client/main.cpp](01_local_tcp/client/main.cpp) | Winsock TCP 클라이언트: connect → send → recv |

**실행 방법:**
```
1. server/main.cpp 빌드 후 실행 (대기 상태)
2. client/main.cpp 빌드 후 실행
3. 서버 콘솔: "클라이언트 접속됨!" 출력
4. 클라이언트 콘솔: "서버로부터 메시지: Hello from Server!" 출력
```

### [02_weather_api_http](02_weather_api_http/) — HTTP + JSON
| 파일 | 설명 |
|------|------|
| [main.cpp](02_weather_api_http/main.cpp) | libcurl로 기상청 API 호출 → jsoncpp로 JSON 파싱 |

**사용 전 필수 설정:**
- [data.go.kr](https://www.data.go.kr)에서 기상청 API 인증키 발급
- `main.cpp` 의 `serviceKey` 변수를 발급받은 키로 교체
- CMakeLists.txt 에서 libcurl, jsoncpp 경로 설정

---

## TCP 서버-클라이언트 흐름

```
[Server]                         [Client]
WSAStartup()                     WSAStartup()
socket()                         socket()
bind()
listen()
accept() ←─────── connect() ─── 
recv()   ←─────── send()    ─── "Hello from Client!"
send()   ──────── recv()    ──→ "Hello from Server!"
closesocket()                    closesocket()
WSACleanup()                     WSACleanup()
```

---

> **앞 단계:** [06_multithreading](../06_multithreading/)  
> **다음 단계:** [08_gui_qt](../08_gui_qt/)
