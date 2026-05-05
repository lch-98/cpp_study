# 18. Advanced Threading (고급 스레딩)

실무 수준의 동시성 프로그램 설계. 가장 어렵지만 가장 강력한 도구들이다.  
이 챕터를 마치면 C++ 동시성의 핵심을 모두 다룬 것이다.

---

## 학습 순서

| 파일 | 주제 | 핵심 API |
|------|------|---------|
| [01_condition_variable.cpp](01_condition_variable.cpp) | 생산자-소비자 패턴, spurious wakeup 방지 | `condition_variable`, `wait(lock, pred)`, `notify_one/all` |
| [02_deadlock.cpp](02_deadlock.cpp) | 교착 상태 발생 원인과 3가지 해결법 | `scoped_lock`, `std::lock`, `adopt_lock` |
| [03_thread_pool.cpp](03_thread_pool.cpp) | 스레드 풀 완전 구현 (future 결과 회수) | `packaged_task`, `invoke_result_t`, worker 루프 |
| [04_atomic.cpp](04_atomic.cpp) | lock-free 원자 연산, CAS | `atomic<T>`, `fetch_add`, `compare_exchange` |

---

## 동시성 도구 선택 가이드

```
단순 카운터/플래그     → atomic<T>
여러 변수 동시 보호    → mutex + lock_guard
조건 만족까지 대기     → condition_variable + unique_lock
여러 mutex 동시 획득   → scoped_lock (C++17)
반복 작업 효율화       → Thread Pool
비동기 결과 전달       → promise + future (17_async 참고)
```

---

## Deadlock 4대 조건

| 조건 | 설명 | 해결 방향 |
|------|------|---------|
| 상호 배제 | 한 번에 하나만 사용 | 공유 자원 최소화 |
| 점유 대기 | 쥔 채로 다른 것 대기 | 모두 한 번에 획득 (scoped_lock) |
| 비선점 | 강제 회수 불가 | try_lock 사용 |
| **순환 대기** | A→B, B→A | **항상 같은 순서로 lock** ← 가장 실용적 |

---

## condition_variable 올바른 사용

```cpp
// 잘못된 패턴 (spurious wakeup에 취약)
cv.wait(lock);
if (q.empty()) { /* 놓칠 수 있음 */ }

// 올바른 패턴 (predicate로 재확인)
cv.wait(lock, [&]{ return !q.empty() || done; });
```

---

## Thread Pool 핵심 구조

```
[enqueue(task)] → tasks queue에 추가 → notify_one
[worker thread] → cv.wait → task 꺼내기 → 실행 → 대기
[~ThreadPool  ] → stop=true → notify_all → join
```

---

> **앞 단계:** [17_async](../17_async/)  
> **마지막 챕터 완료! PROGRESS.md에서 체크하세요.**
