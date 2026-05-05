# C++ Study — From Zero to Real-World

C++ 기초부터 실무 수준까지 단계별로 학습하는 튜토리얼 저장소.  
각 폴더는 독립적인 주제이며, 번호 순서대로 진행하면 자연스럽게 역량을 쌓을 수 있습니다.

진행 상황은 **[PROGRESS.md](PROGRESS.md)** 에서 확인하세요.

---

## 전체 커리큘럼 & 학습 로드맵

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 PHASE 1 — Language Fundamentals  (1~2개월)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 01_basics                입출력, 변수, 연산자, CMake 구조
 02_structs_and_pointers  구조체, 포인터 산술, 배열
 03_classes_oop           클래스 기초, this, setter
 04_algorithms            이진탐색, BFS, DFS, 사이클탐지
 05_exception_handling    try/throw/catch, 예외 설계

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 PHASE 2 — Modern C++ Core  (2~3개월)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 06_multithreading        thread, mutex, race condition
 07_sockets               TCP 소켓, HTTP + JSON API
 08_console_ui            ANSI 색상, 콘솔 메뉴, 이벤트 루프
 09_memory_management     new/delete, 스마트 포인터, RAII
 10_oop_advanced          상속, 다형성, virtual, 추상클래스

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 PHASE 3 — Professional C++  (2~3개월)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 11_templates             함수/클래스 템플릿, 제네릭
 12_stl                   컨테이너, 알고리즘, 이터레이터, 람다
 13_modern_cpp            move semantics, auto, range-for, C++17/20
 14_file_io               fstream, 직렬화, JSON 읽기/쓰기

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 PHASE 4 — Real-World Engineering  (2~3개월)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 15_testing               Google Test, 단위 테스트, TDD
 16_design_patterns       Singleton, Factory, Observer, RAII
 17_async                 std::async, future, promise
 18_advanced_threading    condition_variable, thread pool, deadlock
```

---

## 폴더 구조

| # | 폴더 | 주제 | Phase | 난이도 |
|---|------|------|-------|--------|
| 01 | [01_basics/](01_basics/) | 입출력, 변수, 연산자, CMake | 1 | ⭐ |
| 02 | [02_structs_and_pointers/](02_structs_and_pointers/) | 구조체, 포인터 | 1 | ⭐⭐ |
| 03 | [03_classes_oop/](03_classes_oop/) | 클래스, OOP 기초 | 1 | ⭐⭐ |
| 04 | [04_algorithms/](04_algorithms/) | 이진탐색, BFS, DFS | 1 | ⭐⭐⭐ |
| 05 | [05_exception_handling/](05_exception_handling/) | 예외 처리 | 1 | ⭐⭐ |
| 06 | [06_multithreading/](06_multithreading/) | 멀티스레딩, mutex | 2 | ⭐⭐⭐ |
| 07 | [07_sockets/](07_sockets/) | 소켓, HTTP API | 2 | ⭐⭐⭐⭐ |
| 08 | [08_console_ui/](08_console_ui/) | ANSI 색상, 콘솔 메뉴, 이벤트 루프 | 2 | ⭐⭐⭐ |
| 09 | [09_memory_management/](09_memory_management/) | 스마트 포인터, RAII | 2 | ⭐⭐⭐ |
| 10 | [10_oop_advanced/](10_oop_advanced/) | 상속, 다형성, virtual | 2 | ⭐⭐⭐⭐ |
| 11 | [11_templates/](11_templates/) | 템플릿, 제네릭 | 3 | ⭐⭐⭐⭐ |
| 12 | [12_stl/](12_stl/) | STL 전체 | 3 | ⭐⭐⭐⭐ |
| 13 | [13_modern_cpp/](13_modern_cpp/) | Modern C++11/14/17/20 | 3 | ⭐⭐⭐⭐ |
| 14 | [14_file_io/](14_file_io/) | 파일 I/O, 직렬화 | 3 | ⭐⭐⭐ |
| 15 | [15_testing/](15_testing/) | Google Test, TDD | 4 | ⭐⭐⭐ |
| 16 | [16_design_patterns/](16_design_patterns/) | 디자인 패턴 | 4 | ⭐⭐⭐⭐ |
| 17 | [17_async/](17_async/) | async, future, promise | 4 | ⭐⭐⭐⭐ |
| 18 | [18_advanced_threading/](18_advanced_threading/) | thread pool, deadlock | 4 | ⭐⭐⭐⭐⭐ |

---

## 개발 환경

| 항목 | 버전/도구 |
|------|----------|
| 언어 | C++17 (일부 C++20) |
| 컴파일러 | **MSVC** — Visual Studio 2022 Community |
| 에디터 | VS Code |
| OS | Windows 11 |

> **주의:** Windows 기본 설치 g++ (MinGW 6.3 등)은 C++17 기능 일부가 동작하지 않으므로 사용하지 않습니다.

---

## 개발 환경 구축 (처음부터 따라하기)

### Step 1 — Visual Studio 2022 Community 설치

1. [https://visualstudio.microsoft.com/vs/community/](https://visualstudio.microsoft.com/vs/community/) 에서 설치 파일 다운로드
2. 설치 프로그램 실행 → **"C++를 사용한 데스크톱 개발"** 워크로드 선택 → 설치
3. 설치 완료 후 아래 경로에 `cl.exe`가 생성됩니다:
   ```
   C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\<버전>\bin\Hostx64\x64\cl.exe
   ```

### Step 2 — VS Code 설치

1. [https://code.visualstudio.com/](https://code.visualstudio.com/) 에서 다운로드 후 설치
2. VS Code 실행 후 확장 탭(`Ctrl+Shift+X`)에서 **C/C++ Extension Pack** 설치

### Step 3 — 이 저장소 열기

```cmd
:: 저장소 클론 (Git 설치되어 있는 경우)
git clone <저장소 URL>

:: VS Code로 폴더 열기
code "c:\Users\<사용자명>\Desktop\c++ study"
```

또는 VS Code에서 `파일 → 폴더 열기` 로 직접 선택.

### Step 4 — tasks.json 설정 (Ctrl+Shift+B 빌드 단축키)

`.vscode/tasks.json` 파일을 아래 내용으로 생성하면 단축키로 바로 컴파일할 수 있습니다.

> 이 저장소에는 이미 포함되어 있으므로 추가 설정 없이 바로 사용 가능합니다.

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "MSVC: Build Current File (Ctrl+Shift+B)",
            "type": "shell",
            "command": "cmd",
            "args": [
                "/d", "/c",
                "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\" > nul && cl /std:c++17 /EHsc /W3 /nologo \"${file}\" /Fe\"${fileDirname}\\${fileBasenameNoExtension}.exe\""
            ],
            "options": {
                "shell": { "executable": "cmd.exe", "args": ["/d", "/c"] }
            },
            "group": { "kind": "build", "isDefault": true },
            "problemMatcher": "$msCompile",
            "presentation": { "reveal": "always", "panel": "shared" }
        },
        {
            "label": "MSVC: Build & Run",
            "type": "shell",
            "command": "cmd",
            "args": [
                "/d", "/c",
                "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\" > nul && cl /std:c++17 /EHsc /W3 /nologo \"${file}\" /Fe\"${fileDirname}\\${fileBasenameNoExtension}.exe\" && \"${fileDirname}\\${fileBasenameNoExtension}.exe\""
            ],
            "options": {
                "shell": { "executable": "cmd.exe", "args": ["/d", "/c"] }
            },
            "group": "test",
            "problemMatcher": "$msCompile",
            "presentation": { "reveal": "always", "panel": "shared" }
        },
        {
            "label": "MSVC: Build Winsock (TCP Socket)",
            "type": "shell",
            "command": "cmd",
            "args": [
                "/d", "/c",
                "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\" > nul && cl /std:c++17 /EHsc /W3 /nologo \"${file}\" /Fe\"${fileDirname}\\${fileBasenameNoExtension}.exe\" /link ws2_32.lib"
            ],
            "options": {
                "shell": { "executable": "cmd.exe", "args": ["/d", "/c"] }
            },
            "group": "build",
            "problemMatcher": "$msCompile",
            "presentation": { "reveal": "always", "panel": "shared" }
        },
        {
            "label": "Run Executable",
            "type": "shell",
            "command": "\"${fileDirname}\\${fileBasenameNoExtension}.exe\"",
            "options": {
                "shell": { "executable": "cmd.exe", "args": ["/d", "/c"] }
            },
            "group": "test",
            "presentation": { "reveal": "always", "panel": "shared" }
        }
    ]
}
```

> **왜 이렇게 복잡한가?**  
> VS Code 기본 터미널(PowerShell)에서는 `cl.exe`를 찾지 못합니다.  
> `cmd.exe`로 우회하고 `vcvars64.bat`를 먼저 실행해야 MSVC 환경 변수가 설정됩니다.

---

## 빌드 방법

### 방법 1: Ctrl+Shift+B (가장 빠름 — 권장)

1. VS Code에서 `.cpp` 파일 열기
2. `Ctrl+Shift+B` → 자동으로 현재 파일 컴파일
3. 같은 폴더에 `.exe` 생성됨
4. 터미널(`Ctrl+`` `)에서 실행:
   ```cmd
   .\파일명.exe
   ```

### 방법 2: 태스크 목록에서 선택

`Ctrl+Shift+P` → `Tasks: Run Task` → 원하는 태스크 선택:

| 태스크 | 용도 |
|--------|------|
| `MSVC: Build Current File` | 현재 파일만 컴파일 |
| `MSVC: Build & Run` | 컴파일 후 즉시 실행 |
| `MSVC: Build Winsock (TCP Socket)` | 소켓 파일 컴파일 (`ws2_32.lib` 링크 포함) |
| `Run Executable` | 이미 빌드된 `.exe` 실행 |

### 방법 3: Developer Command Prompt에서 직접 컴파일

1. 시작 메뉴 → `Developer Command Prompt for VS 2022` 검색 후 실행
2. 해당 폴더로 이동 후 컴파일:

```cmd
cd "c:\Users\<사용자명>\Desktop\c++ study\01_basics\01_io"

cl /std:c++17 /EHsc output.cpp
output.exe
```

---

## 주요 컴파일 옵션

| 옵션 | 설명 |
|------|------|
| `/std:c++17` | C++17 표준 사용 |
| `/EHsc` | 예외 처리 활성화 (필수) |
| `/W3` | 경고 레벨 3 (권장) |
| `/nologo` | 컴파일러 배너 숨김 |
| `/Fe파일명.exe` | 출력 실행 파일 이름 지정 |
| `/O2` | 최적화 (릴리즈용) |
| `/Zi` | 디버그 정보 생성 |
| `/link ws2_32.lib` | Winsock 링크 (소켓 파일 전용) |

---

## 파일 읽는 방법

모든 `.cpp` 파일 상단:
```cpp
/*
 * [Topic] 주제 이름
 * 한 줄 요약
 *
 * Key points:
 *   - 핵심 개념
 * Practice:
 *   - 직접 해볼 것
 */
```
