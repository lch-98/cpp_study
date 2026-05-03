# 03. Classes & OOP (클래스와 객체지향)

구조체에서 클래스로 넘어가며 객체지향의 핵심 개념을 익힙니다.

---

## 학습 순서

| 파일 | 주제 | 설명 |
|------|------|------|
| [struct_class_pointer.cpp](struct_class_pointer.cpp) | struct vs class | 기본 접근 제어 차이, `->` 연산자 |
| [this_pointer_and_setter.cpp](this_pointer_and_setter.cpp) | this 포인터 & setter | 멤버 변수와 매개변수 이름 충돌 해결, setter 패턴 |

---

## 핵심 개념 요약

```cpp
// struct : 기본 public / class : 기본 private
struct S { int x; };   // x 외부 접근 가능
class  C { int x; };   // x 외부 접근 불가

// -> 연산자
ptr->job  ==  (*ptr).job

// this 포인터: 자기 자신 객체를 가리킴
void setInfo(string job) {
    this->job = job;  // 멤버변수(this->job) ← 매개변수(job)
}
```

### OOP 4대 원칙 (이후 학습 방향)
| 원칙 | 키워드 |
|------|--------|
| 캡슐화 | `private` + getter/setter |
| 상속 | `class Child : public Parent` |
| 다형성 | `virtual` / `override` |
| 추상화 | `abstract class` / 순수 가상 함수 |

> **앞 단계:** [02_structs_and_pointers](../02_structs_and_pointers/)  
> **다음 단계:** [04_algorithms](../04_algorithms/)
