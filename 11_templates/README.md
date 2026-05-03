# 11. Templates (템플릿)

타입에 독립적인 제네릭 코드를 작성한다. STL이 전부 이 위에서 만들어진다.

---

## 학습 순서

| 파일 | 주제 | 핵심 키워드 |
|------|------|------------|
| [01_function_template.cpp](01_function_template.cpp) | 함수 템플릿 | `template<typename T>`, 타입 추론, 특수화 |
| [02_class_template.cpp](02_class_template.cpp) | 클래스 템플릿 | Stack 구현, 기본 타입 매개변수 |
| [03_template_specialization.cpp](03_template_specialization.cpp) | 전체/부분 특수화 | `template<>`, 포인터 특수화 |
| [04_variadic_template.cpp](04_variadic_template.cpp) | 가변 인자 템플릿 | `...`, `sizeof...`, fold expression |

---

## 핵심 개념

```cpp
// 기본 문법
template<typename T>
T add(T a, T b) { return a + b; }

// 호출 (타입 추론)
add(1, 2);        // T = int
add(1.0, 2.0);    // T = double

// 명시적 지정
add<float>(1, 2); // T = float

// 클래스 템플릿
template<typename T>
class Box { T value; };

Box<int> b1;
Box<string> b2;
```

### 왜 템플릿인가?
- 같은 로직을 int, double, string 등 모든 타입에 재사용
- 컴파일 타임에 타입 확인 (런타임 오버헤드 없음)
- STL의 `vector<int>`, `map<string, int>` 전부 클래스 템플릿

> **앞 단계:** [10_oop_advanced](../10_oop_advanced/)
> **다음 단계:** [12_stl](../12_stl/)
