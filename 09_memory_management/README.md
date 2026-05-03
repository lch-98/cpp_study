# 09. Memory Management (메모리 관리)

C++에서 메모리를 안전하게 다루는 방법. new/delete부터 스마트 포인터, RAII까지.

---

## 학습 순서

| 파일 | 주제 | 핵심 키워드 |
|------|------|------------|
| [01_new_delete.cpp](01_new_delete.cpp) | 힙 vs 스택, new/delete | `new`, `delete`, `delete[]` |
| [02_memory_leak.cpp](02_memory_leak.cpp) | 누수 패턴 3가지 | 누수 원인, 포인터 덮어쓰기 |
| [03_unique_ptr.cpp](03_unique_ptr.cpp) | 단독 소유권 | `unique_ptr`, `make_unique`, `move` |
| [04_shared_ptr.cpp](04_shared_ptr.cpp) | 공유 소유권 | `shared_ptr`, `use_count`, 참조 카운팅 |
| [05_weak_ptr.cpp](05_weak_ptr.cpp) | 순환 참조 해결 | `weak_ptr`, `lock()`, `expired()` |
| [06_raii.cpp](06_raii.cpp) | RAII 패턴 | 생성자 획득, 소멸자 해제 |

---

## 핵심 개념

### 소유권 모델
```
raw pointer    → 소유권 불명확, 수동 관리
unique_ptr     → 단독 소유, 이동만 가능
shared_ptr     → 공유 소유, 참조 카운팅
weak_ptr       → 비소유 참조, 순환 참조 방지
```

### 스마트 포인터 선택 기준
```cpp
// 소유자가 하나 → unique_ptr (기본 선택)
auto p = make_unique<Foo>();

// 여러 곳에서 공유 → shared_ptr
auto p = make_shared<Foo>();

// 순환 참조 우려 → weak_ptr (한 쪽에 사용)
weak_ptr<Foo> wp = sp;
```

### RAII 골든 룰
- 자원을 획득하는 즉시 관리 객체에 넣는다
- 관리 객체는 소멸자에서 자원을 해제한다
- 복사 생성자/대입 연산자를 금지(`= delete`)하거나 명시적으로 정의한다

> **앞 단계:** [08_gui_qt](../08_gui_qt/)
> **다음 단계:** [10_oop_advanced](../10_oop_advanced/)
