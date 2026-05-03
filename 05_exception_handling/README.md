# 05. Exception Handling (예외 처리)

C++의 예외 처리 메커니즘(`try` / `throw` / `catch`)을 익힙니다.

---

## 파일

| 파일 | 설명 |
|------|------|
| [try_throw_catch.cpp](try_throw_catch.cpp) | 타입별 throw와 catch 동작 확인 |

---

## 핵심 개념

```cpp
try {
    throw 1;        // int 타입 예외 발생
    throw -1.0f;    // float 타입 예외 발생
    throw 'Z';      // char 타입 예외 발생
}
catch (int a) {
    // int 타입만 처리
}
catch (...) {
    // 나머지 모든 타입 처리 (catch-all)
}
```

### 주요 규칙
- `throw` 이후의 코드는 실행되지 않음 → 즉시 `catch` 블록으로 이동
- 타입이 정확히 일치하는 `catch` 블록이 처리
- `catch(...)` 는 가장 마지막에 위치해야 함
- 실무에서는 `std::exception`을 상속한 커스텀 예외 클래스를 사용하는 것이 권장됨

---

> **앞 단계:** [04_algorithms](../04_algorithms/)  
> **다음 단계:** [06_multithreading](../06_multithreading/)
