# 17. Async Programming (비동기 프로그래밍)

스레드보다 높은 수준의 추상화로 비동기 작업을 간결하게 표현한다.  
직접 thread를 관리하지 않아도 결과를 받고, 예외를 전파하고, 실행 시점을 제어할 수 있다.

---

## 학습 순서

| 파일 | 주제 | 핵심 API |
|------|------|---------|
| [01_async_future.cpp](01_async_future.cpp) | async 기본, 병렬 계산, 예외 전파 | `async`, `future::get`, `launch::async/deferred` |
| [02_promise.cpp](02_promise.cpp) | 값 직접 설정, 예외 전달, shared_future | `promise::set_value`, `shared_future`, `wait_for` |
| [03_packaged_task.cpp](03_packaged_task.cpp) | callable을 future에 묶기, 실행 시점 분리 | `packaged_task`, 작업 큐 패턴 |

---

## thread vs async 비교

| | `thread` | `async` |
|-|----------|---------|
| 수준 | 저수준 | 고수준 |
| 반환값 | 없음 (공유 변수 필요) | `future`로 자동 전달 |
| 예외 | 프로그램 종료 | `future::get()`으로 전파 |
| 실행 제어 | 직접 | `launch` 정책으로 |
| 정리 | `join`/`detach` 필수 | 자동 |

---

## 핵심 패턴

```cpp
// 병렬 실행 후 결과 수집
auto f1 = async(launch::async, task1, arg1);
auto f2 = async(launch::async, task2, arg2);
auto r1 = f1.get();  // 완료까지 대기
auto r2 = f2.get();

// 타임아웃 대기
auto status = fut.wait_for(chrono::milliseconds(100));
if (status == future_status::ready) { ... }
else if (status == future_status::timeout) { ... }

// promise로 스레드 간 채널
promise<int> p;
auto f = p.get_future();
thread t([](promise<int> p){ p.set_value(42); }, move(p));
cout << f.get();
t.join();
```

---

## 연결 관계

```
promise<T>          →  future<T>       (1:1, 한 번만 get)
promise<T>.share()  →  shared_future<T> (1:N, 여러 번 get)
packaged_task<R()>  →  future<R>       (실행 시점 분리)
async(...)          →  future<R>       (자동 생성)
```

> **앞 단계:** [16_design_patterns](../16_design_patterns/)  
> **다음 단계:** [18_advanced_threading](../18_advanced_threading/)
