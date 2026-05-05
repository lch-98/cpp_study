# C++ Study — Progress Tracker

> 체크박스를 채우면서 진행하세요. 각 항목 옆에 완료 날짜를 적는 것을 권장합니다.
> 예) `- [x] output.cpp 학습 — 2025-05-10`

---

## Phase 1 — Language Fundamentals
**목표:** C++ 문법과 메모리 모델의 기초를 탄탄하게 잡는다.  
**권장 기간:** 1~2개월 (주 3~4회, 회당 1~2시간)

---

### 01. Basics (기초 문법)
**학습 목표:** 입출력, 변수, 타입, 포인터/참조, CMake 빌드 시스템

- [ x ] **01_io** — 입출력
  - [ x ] `output.cpp` — cout, endl
  - [ x ] `input.cpp` — cin, string, int 입력

- [ ] **02_variables** — 변수와 메모리
  - [ ] `reference_pointer.cpp` — 참조자 vs 포인터 차이
  - [ ] `value_reference_pointer.cpp` — 인자 전달 세 가지 방식
  - [ ] `static_const.cpp` — static 지역변수, const 포인터
  - [ ] `volatile_const.cpp` — const vs volatile

- [ ] **03_operators** — 연산자
  - [ ] `a++_++a.cpp` — 후위/전위 증가 연산자

- [ ] **04_project_structure** — CMake 프로젝트 구조
  - [ ] 헤더/소스 분리 구조 이해
  - [ ] `cmake ..` && `cmake --build .` 직접 빌드해보기
  - [ ] `#pragma once` 의 역할 이해

---

### 02. Structs & Pointers (구조체와 포인터)
**학습 목표:** 구조체로 데이터를 묶고, 포인터로 메모리를 직접 다룬다.

- [ ] `pointer.cpp` — 포인터 선언, 역참조, 주소 출력
- [ ] `ptr_arr.cpp` — 포인터 산술, `ptr[i]` == `*(ptr+i)`
- [ ] `struct.cpp` — 구조체 선언과 멤버 접근
- [ ] `struct_ptr.cpp` — 구조체 배열을 포인터로 함수 전달
- [ ] `struct_arr.cpp` — 포인터 멤버를 가진 구조체, typedef
- [ ] `struct_func.cpp` — 포인터 매개변수로 원본 값 수정

---

### 03. Classes & OOP 기초
**학습 목표:** 클래스의 기본 구조와 객체지향의 시작점을 이해한다.

- [ ] `struct_class_pointer.cpp` — struct vs class 접근제어 차이, `->` 연산자
- [ ] `this_pointer_and_setter.cpp` — this 포인터, setter 패턴
- [ ] **추가 학습** (10_oop_advanced에서 심화)
  - [ ] 생성자/소멸자 동작 이해
  - [ ] 캡슐화 개념 이해

---

### 04. Algorithms (기본 알고리즘)
**학습 목표:** 핵심 탐색 알고리즘을 직접 구현하며 자료구조 감각을 키운다.

- [ ] `binary_search.cpp` — 이진 탐색, O(log n)
- [ ] `bfs_dfs.cpp` — BFS(queue), DFS(재귀), 미로 탐색
- [ ] `graph_with_bfs.cpp` — 무방향 그래프 사이클 탐지
- [ ] **직접 해보기**
  - [ ] binary_search를 재귀로 다시 구현해보기
  - [ ] DFS를 스택(반복문)으로 다시 구현해보기

---

### 05. Exception Handling (예외 처리)
**학습 목표:** 예외 처리 흐름과 타입별 catch를 이해한다.

- [ ] `try_throw_catch.cpp` — try/throw/catch, catch-all
- [ ] **추가 학습**
  - [ ] `std::exception` 상속 커스텀 예외 클래스 직접 작성
  - [ ] `noexcept` 키워드 의미 파악

---

## Phase 2 — Modern C++ Core
**목표:** 실무 코드에서 실제로 쓰이는 핵심 기능들을 익힌다.  
**권장 기간:** 2~3개월 (주 3~4회, 회당 1~2시간)

---

### 06. Multithreading (멀티스레딩)
**학습 목표:** 스레드 생성, 동기화, 경쟁 상태를 이해하고 해결한다.

- [ ] `nomutex_print.cpp` — mutex 없는 출력 혼재
- [ ] `mutex_print.cpp` — lock_guard로 출력 보호
- [ ] `problem_multithreading.cpp` — race condition 현상 확인
- [ ] `mutex_multithreading.cpp` — mutex로 경쟁 상태 해결
- [ ] **추가 학습** (18_advanced_threading에서 심화)
  - [ ] `join()` vs `detach()` 차이 파악
  - [ ] `lock_guard` vs `unique_lock` 차이 파악

---

### 07. Sockets (소켓 통신)
**학습 목표:** TCP/UDP 소켓의 흐름을 이해하고 다양한 서버 패턴을 구현한다.

- [ ] `01_local_tcp/server/main.cpp` — Winsock TCP 서버 기초
- [ ] `01_local_tcp/client/main.cpp` — Winsock TCP 클라이언트 기초
- [ ] `02_http_raw.cpp` — raw socket으로 HTTP GET 직접 구현 (example.com)
- [ ] `03_echo_server.cpp` — 반복 수신 Echo 서버, SO_REUSEADDR
- [ ] `04_multi_client.cpp` — select()로 단일 스레드 다중 클라이언트 처리
- [ ] `05_udp.cpp` — UDP 비연결형 핑퐁 통신 (두 터미널로 실행)
- [ ] `06_threaded_server.cpp` — 스레드 기반 다중 클라이언트 서버
- [ ] **직접 해보기**
  - [ ] `04_multi_client.cpp`의 브로드캐스트를 채팅방으로 확장해보기
  - [ ] `06_threaded_server.cpp`에 최대 접속자 수 제한 추가해보기

---

### 08. Console UI (콘솔 UI & 이벤트 루프)
**학습 목표:** ANSI 코드로 색상/커서를 제어하고, GUI의 핵심 원리인 이벤트 루프를 직접 구현한다.

- [ ] `01_ansi_colors.cpp` — ANSI 색상, 스타일, 진행률 바
- [ ] `02_console_menu.cpp` — 방향키 인터랙티브 메뉴, 서브메뉴
- [ ] `03_event_loop.cpp` — Poll → Dispatch → Render 이벤트 루프 (~60fps)
- [ ] **직접 해보기**
  - [ ] 진행률 바를 실제 작업(파일 읽기 등)에 붙여보기
  - [ ] `03_event_loop.cpp`에 'a'/'d' 키로 움직이는 플레이어 추가해보기

---

### 09. Memory Management (메모리 관리)
**학습 목표:** 힙 메모리를 직접 다루고, 스마트 포인터로 안전하게 관리한다.

- [ ] `01_new_delete.cpp` — new/delete, 힙 vs 스택
- [ ] `02_memory_leak.cpp` — 메모리 누수 발생 vs 방지
- [ ] `03_unique_ptr.cpp` — unique_ptr, 단독 소유권
- [ ] `04_shared_ptr.cpp` — shared_ptr, 참조 카운팅
- [ ] `05_weak_ptr.cpp` — weak_ptr, 순환 참조 해결
- [ ] `06_raii.cpp` — RAII 패턴, 자원 자동 해제
- [ ] **직접 해보기**
  - [ ] raw pointer를 unique_ptr로 교체해보기
  - [ ] 순환 참조 버그를 weak_ptr로 고쳐보기

---

### 10. OOP Advanced (객체지향 심화)
**학습 목표:** 상속, 다형성, 추상 클래스로 확장 가능한 설계를 한다.

- [ ] `01_inheritance.cpp` — 기본 상속, 접근 제어
- [ ] `02_virtual.cpp` — virtual 함수, 동적 바인딩
- [ ] `03_pure_virtual.cpp` — 순수 가상 함수, 추상 클래스
- [ ] `04_override_final.cpp` — override, final 키워드
- [ ] `05_multiple_inheritance.cpp` — 다중 상속, 다이아몬드 문제
- [ ] `06_operator_overloading.cpp` — 연산자 오버로딩
- [ ] **직접 해보기**
  - [ ] 도형 계층(Shape → Circle, Rectangle) 직접 설계해보기
  - [ ] `==` 연산자 오버로딩해보기

---

## Phase 3 — Professional C++
**목표:** 제네릭 프로그래밍과 Modern C++ 관용구를 내 것으로 만든다.  
**권장 기간:** 2~3개월 (주 3~4회, 회당 1~2시간)

---

### 11. Templates (템플릿)
**학습 목표:** 타입에 독립적인 제네릭 코드를 작성한다.

- [ ] `01_function_template.cpp` — 함수 템플릿, 타입 추론
- [ ] `02_class_template.cpp` — 클래스 템플릿, Stack 구현
- [ ] `03_template_specialization.cpp` — 특수화(전체/부분)
- [ ] `04_variadic_template.cpp` — 가변 인자 템플릿
- [ ] **직접 해보기**
  - [ ] 제네릭 `Pair<T, U>` 클래스 직접 구현해보기

---

### 12. STL (표준 라이브러리)
**학습 목표:** STL 컨테이너와 알고리즘을 자유롭게 활용한다.

- [ ] `01_vector.cpp` — vector, 동적 배열, emplace_back
- [ ] `02_map_set.cpp` — map, set, unordered_map, 정렬 컨테이너
- [ ] `03_deque_list.cpp` — deque, list, 삽입/삭제 특성
- [ ] `04_stack_queue.cpp` — stack, queue, priority_queue
- [ ] `05_iterators.cpp` — 이터레이터, begin/end, advance
- [ ] `06_algorithms.cpp` — sort, find, transform, accumulate
- [ ] `07_lambda.cpp` — 람다 표현식, 캡처, 함수형 스타일
- [ ] **직접 해보기**
  - [ ] 벡터를 람다+sort로 커스텀 정렬해보기
  - [ ] map으로 단어 빈도 카운터 만들어보기

---

### 13. Modern C++ (C++11/14/17/20)
**학습 목표:** 현대 C++의 핵심 기능으로 더 안전하고 빠른 코드를 쓴다.

- [ ] `01_auto_decltype.cpp` — auto, decltype, 타입 추론
- [ ] `02_range_for.cpp` — range-based for, 구조적 바인딩
- [ ] `03_move_semantics.cpp` — rvalue 참조, std::move, 복사 제거
- [ ] `04_perfect_forwarding.cpp` — std::forward, 유니버설 참조
- [ ] `05_smart_ptrs_modern.cpp` — make_unique, make_shared
- [ ] `06_optional_variant.cpp` — std::optional, std::variant (C++17)
- [ ] `07_constexpr.cpp` — constexpr, 컴파일 타임 계산
- [ ] `08_structured_bindings.cpp` — 구조적 바인딩 (C++17)
- [ ] **직접 해보기**
  - [ ] 기존 코드에서 raw loop를 range-for로 바꿔보기
  - [ ] 반환값에 std::optional 적용해보기

---

### 14. File I/O & Serialization (파일 입출력)
**학습 목표:** 파일 읽기/쓰기와 데이터 직렬화를 다룬다.

- [ ] `01_fstream_basic.cpp` — ifstream, ofstream, 텍스트 파일
- [ ] `02_binary_io.cpp` — 바이너리 파일 읽기/쓰기
- [ ] `03_csv_parser.cpp` — CSV 파싱
- [ ] `04_json_readwrite.cpp` — jsoncpp로 JSON 읽기/쓰기
- [ ] **직접 해보기**
  - [ ] 프로그램 설정을 JSON 파일로 저장/불러오기 구현

---

## Phase 4 — Real-World Engineering
**목표:** 실무에서 통용되는 코드 품질과 설계를 갖춘다.  
**권장 기간:** 2~3개월 (주 3~4회, 회당 1~2시간)

---

### 15. Testing (단위 테스트)
**학습 목표:** 자동화 테스트를 작성해 코드 품질을 검증한다.

- [ ] `01_gtest_basic.cpp` — Google Test 설치 및 기본 assert
- [ ] `02_test_fixtures.cpp` — TEST_F, 픽스처, SetUp/TearDown
- [ ] `03_mock_concept.cpp` — 의존성 주입, 테스트 가능한 설계
- [ ] `04_tdd_example.cpp` — TDD 사이클 (Red → Green → Refactor)
- [ ] **직접 해보기**
  - [ ] 기존 binary_search.cpp에 대한 테스트 3개 이상 작성

---

### 16. Design Patterns (디자인 패턴)
**학습 목표:** 반복되는 설계 문제의 표준 해법을 익힌다.

- [ ] `01_singleton.cpp` — 싱글톤 (thread-safe 버전 포함)
- [ ] `02_factory.cpp` — 팩토리 메서드, 추상 팩토리
- [ ] `03_observer.cpp` — 옵저버 (이벤트/콜백 시스템)
- [ ] `04_strategy.cpp` — 전략 패턴 (알고리즘 교체 가능)
- [ ] `05_raii_pattern.cpp` — RAII를 패턴으로 설계하기
- [ ] **직접 해보기**
  - [ ] 옵저버로 간단한 이벤트 버스 구현해보기

---

### 17. Async Programming (비동기 프로그래밍)
**학습 목표:** 스레드보다 상위 레벨의 비동기 도구를 다룬다.

- [ ] `01_async_future.cpp` — std::async, std::future, get()
- [ ] `02_promise.cpp` — std::promise, 수동 값 전달
- [ ] `03_packaged_task.cpp` — packaged_task, callable 래핑
- [ ] `04_async_vs_thread.cpp` — async vs thread 비교
- [ ] **직접 해보기**
  - [ ] 여러 URL을 비동기로 동시 요청하는 코드 작성

---

### 18. Advanced Threading (고급 스레딩)
**학습 목표:** 실무 수준의 동시성 설계와 문제 해결 능력을 갖춘다.

- [ ] `01_condition_variable.cpp` — condition_variable, 생산자-소비자
- [ ] `02_deadlock.cpp` — 교착 상태 발생 원인과 해결
- [ ] `03_scoped_lock.cpp` — std::scoped_lock, 다중 mutex 안전 획득
- [ ] `04_thread_pool.cpp` — 직접 구현하는 Thread Pool
- [ ] `05_atomic.cpp` — std::atomic, lock-free 카운터
- [ ] `06_memory_order.cpp` — memory_order, happens-before
- [ ] **직접 해보기**
  - [ ] thread_pool에 작업 우선순위 기능 추가해보기
  - [ ] deadlock 코드를 scoped_lock으로 고쳐보기

---

## 전체 진행 요약

| Phase | 기간 | 폴더 | 진행률 |
|-------|------|------|--------|
| Phase 1 — Fundamentals | 1~2개월 | 01~05 | 0 / 5 완료 |
| Phase 2 — Modern Core | 2~3개월 | 06~10 | 0 / 5 완료 |
| Phase 3 — Professional | 2~3개월 | 11~14 | 0 / 4 완료 |
| Phase 4 — Real-World | 2~3개월 | 15~18 | 0 / 4 완료 |
| **합계** | **7~11개월** | **18개 챕터** | **0 / 18 완료** |

---

## 학습 방법 가이드

### 하루 세션 구성 (1~2시간)
```
[15분] 이전 세션 복습 — 어제 코드 다시 읽기
[40분] 새 개념 코드 실행 + 직접 수정해보기
[15분] Practice 항목 중 하나 직접 구현
[10분] 오늘 배운 것 한 줄 메모 (주석이나 노트)
```

### Phase별 공부 방법
- **Phase 1:** 코드를 반드시 직접 타이핑해서 실행. 복붙 금지.
- **Phase 2:** 각 예제를 수정하며 "이러면 어떻게 될까?" 실험 위주.
- **Phase 3:** 공식 cppreference.com 문서와 함께 읽기. 문서 읽는 습관 들이기.
- **Phase 4:** 미니 프로젝트에 적용. 단순 예제보다 실제 문제 해결에 써보기.

### 막혔을 때
1. 오류 메시지를 정확히 읽는다 (컴파일러는 거짓말하지 않는다)
2. 해당 폴더의 `README.md` 핵심 개념 재확인
3. [cppreference.com](https://en.cppreference.com) 에서 해당 함수/클래스 검색
4. 작은 독립 파일로 문제를 격리해서 재현해본다
