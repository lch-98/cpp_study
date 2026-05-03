# 10. OOP Advanced (객체지향 심화)

상속, 다형성, 추상 클래스로 확장 가능하고 유지보수하기 쉬운 설계를 한다.

---

## 학습 순서

| 파일 | 주제 | 핵심 키워드 |
|------|------|------------|
| [01_inheritance.cpp](01_inheritance.cpp) | 기본 상속 | `public`, `protected`, 생성자 체인 |
| [02_virtual.cpp](02_virtual.cpp) | 가상 함수, 다형성 | `virtual`, vtable, 동적 바인딩 |
| [03_pure_virtual.cpp](03_pure_virtual.cpp) | 순수 가상, 추상 클래스 | `= 0`, 인터페이스 패턴 |
| [04_override_final.cpp](04_override_final.cpp) | override, final | 컴파일 타임 안전망 |
| [05_operator_overloading.cpp](05_operator_overloading.cpp) | 연산자 오버로딩 | `operator+`, `friend`, `<<` |

---

## 핵심 개념

### 상속 vs 다형성
```cpp
// 상속: 코드 재사용
class Dog : public Animal { ... };

// 다형성: 동일 인터페이스로 다양한 구현
Animal* a = new Dog();
a->speak();  // Dog::speak() 호출 (virtual 덕분에)
```

### virtual 소멸자가 필요한 이유
```cpp
Animal* a = new Dog();
delete a;  // virtual ~Animal() 없으면 Dog 소멸자 미호출 → 메모리 누수
```

### 설계 원칙 (SOLID 맛보기)
- **S** — 단일 책임: 클래스는 하나의 역할만
- **O** — 개방/폐쇄: 상속으로 확장, 수정은 최소화
- **L** — 리스코프 치환: 자식은 부모를 대체할 수 있어야 함
- **I** — 인터페이스 분리: 필요한 인터페이스만 구현
- **D** — 의존성 역전: 추상(인터페이스)에 의존, 구현에 의존 X

> **앞 단계:** [09_memory_management](../09_memory_management/)
> **다음 단계:** [11_templates](../11_templates/)
