# 06. Multithreading (멀티스레딩)

C++ 표준 라이브러리(`<thread>`, `<mutex>`)로 멀티스레딩을 구현하고,
경쟁 상태(Race Condition)의 문제와 해결 방법을 비교합니다.

---

## 학습 순서

### [01_output_examples](01_output_examples/) — 출력 혼재 현상
| 파일 | 설명 |
|------|------|
| [nomutex_print.cpp](01_output_examples/nomutex_print.cpp) | mutex 없이 두 스레드가 동시에 cout → 출력 섞임 |
| [mutex_print.cpp](01_output_examples/mutex_print.cpp) | `lock_guard`로 출력 보호 → 깔끔한 출력 |

### [02_race_condition](02_race_condition/) — 경쟁 상태
| 파일 | 설명 |
|------|------|
| [problem_multithreading.cpp](02_race_condition/problem_multithreading.cpp) | 뮤텍스 없이 공유 카운터 증가 → 값 유실 발생 |
| [mutex_multithreading.cpp](02_race_condition/mutex_multithreading.cpp) | mutex로 보호 → 항상 1,000,000 출력 |

---

## 핵심 개념

```cpp
// 스레드 생성과 대기
thread t1(func, arg);
t1.join();  // t1이 끝날 때까지 메인 스레드 대기

// mutex 직접 사용
mutex mtx;
mtx.lock();
// 임계 구역 (한 스레드만 진입)
mtx.unlock();

// lock_guard (RAII - 자동 unlock, 권장)
lock_guard<mutex> lock(mtx);
// 스코프 종료 시 자동으로 unlock
```

### Race Condition 이 발생하는 이유
`counter++` 는 실제로 세 단계:
1. 메모리에서 값 읽기
2. +1 연산
3. 메모리에 저장

→ 두 스레드가 1번과 3번 사이에 끼어들면 증가분이 사라짐

---

> **앞 단계:** [05_exception_handling](../05_exception_handling/)  
> **다음 단계:** [07_sockets](../07_sockets/)
