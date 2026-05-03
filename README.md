# C++ Study — From Zero to Real-World

C++ 기초부터 실무 수준까지 단계별로 학습하는 튜토리얼 저장소.  
각 폴더는 독립적인 주제이며, 번호 순서대로 진행하면 자연스럽게 역량이 쌓입니다.

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
 08_gui_qt                Qt 기본 GUI
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
| 08 | [08_gui_qt/](08_gui_qt/) | Qt GUI | 2 | ⭐⭐⭐ |
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
| 빌드 | CMake 3.10+ |
| 컴파일러 | MSVC / g++ |
| 에디터 | VS Code |
| OS | Windows 11 |
| 외부 라이브러리 | Winsock2, libcurl, jsoncpp, Qt6, Google Test |

---

## 빠른 시작

```bash
# 단일 파일
g++ -std=c++17 -o output filename.cpp

# CMake 프로젝트
mkdir build && cd build
cmake .. && cmake --build .
```

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
