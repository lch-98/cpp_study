# 08. Console UI & Event Loop

Qt 설치 없이 표준 라이브러리 + Windows API만으로 GUI의 핵심 원리를 익힌다.  
ANSI 이스케이프 코드로 색상/커서를 제어하고, 이벤트 루프 패턴을 직접 구현한다.

> **Qt 원본 예제는 `QT기본실행/` 폴더에 보존되어 있음.**  
> Qt 설치 시: `cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64"` 후 빌드 가능.

---

## 학습 순서

| 파일 | 주제 | 핵심 개념 |
|------|------|---------|
| [01_ansi_colors.cpp](01_ansi_colors.cpp) | ANSI 색상·스타일·진행률 바 | `\033[색상m`, `\033[0m`, 진행률 바 |
| [02_console_menu.cpp](02_console_menu.cpp) | 방향키 인터랙티브 메뉴 | `_getch()`, 상태 기반 렌더링, 서브메뉴 |
| [03_event_loop.cpp](03_event_loop.cpp) | 이벤트 루프 패턴 | Poll → Dispatch → Render, ~60fps |

---

## 빌드

```cmd
cl /std:c++17 /EHsc 01_ansi_colors.cpp
cl /std:c++17 /EHsc 02_console_menu.cpp
cl /std:c++17 /EHsc 03_event_loop.cpp
```

---

## ANSI 이스케이프 코드 치트시트

```cpp
// 색상 (전경)
"\033[31m" → 빨강   "\033[32m" → 초록   "\033[33m" → 노랑
"\033[34m" → 파랑   "\033[35m" → 자홍   "\033[36m" → 청록
// 밝은 색: 30 → 90 대로 변경 (예: "\033[91m" 밝은 빨강)

// 배경: 전경 코드 + 10 (예: "\033[41m" 빨간 배경)

// 스타일
"\033[0m"  → 초기화   "\033[1m" → 굵게   "\033[4m" → 밑줄

// 커서
"\033[2J\033[H"     → 화면 지우기
"\033[행;열H"       → 커서 이동
"\033[?25l"         → 커서 숨기기
"\033[?25h"         → 커서 보이기
```

## Qt와의 개념 대응

| 이 예제 | Qt 대응 |
|--------|---------|
| `while(running)` 루프 | `app.exec()` |
| `pollEvent()` | 이벤트 큐 처리 |
| `handleEvent()` | `keyPressEvent()`, 슬롯 |
| `render()` | `paintEvent()`, `update()` |
| `Sleep(16)` | `QTimer` (16ms = ~60fps) |

> **앞 단계:** [07_sockets](../07_sockets/)  
> **다음 단계:** [09_memory_management](../09_memory_management/)
