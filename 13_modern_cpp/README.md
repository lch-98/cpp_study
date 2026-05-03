# 13. Modern C++ (C++11/14/17/20)

현대 C++의 핵심 기능으로 더 안전하고, 빠르고, 읽기 쉬운 코드를 작성한다.

---

## 학습 순서

| 파일 | 주제 | C++ 버전 |
|------|------|---------|
| [01_auto_decltype.cpp](01_auto_decltype.cpp) | 타입 추론 | C++11 |
| [02_move_semantics.cpp](02_move_semantics.cpp) | 이동 시멘틱, Rule of Five | C++11 |
| [03_range_for_structured_bindings.cpp](03_range_for_structured_bindings.cpp) | range-for, 구조적 바인딩 | C++11/17 |
| [04_optional_variant.cpp](04_optional_variant.cpp) | optional, variant | C++17 |
| [05_constexpr.cpp](05_constexpr.cpp) | 컴파일 타임 계산 | C++11/14/17 |
| [06_smart_ptr_modern.cpp](06_smart_ptr_modern.cpp) | 스마트 포인터 실무 패턴 | C++11/14 |

---

## 핵심 규칙 (실무 체크리스트)

```
✓ using namespace std; 는 헤더 파일에 절대 쓰지 않는다
✓ new/delete 대신 make_unique/make_shared 사용
✓ 컨테이너 순회 시 const auto& 사용
✓ 실패 가능한 반환은 optional<T> 사용
✓ nullptr 사용 (NULL 금지)
✓ override 키워드로 가상 함수 재정의 명시
✓ noexcept 이동 생성자/대입 연산자
```

> **앞 단계:** [12_stl](../12_stl/)
> **다음 단계:** [14_file_io](../14_file_io/)
