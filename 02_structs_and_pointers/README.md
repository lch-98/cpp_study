# 02. Structs & Pointers (구조체와 포인터)

구조체로 데이터를 묶고, 포인터로 메모리를 직접 다루는 방법을 익힙니다.

---

## 학습 순서

| 파일 | 주제 | 설명 |
|------|------|------|
| [pointer.cpp](pointer.cpp) | 기본 포인터 | 포인터 선언, 역참조(`*`), 주소 출력 |
| [ptr_arr.cpp](ptr_arr.cpp) | 포인터 산술 | `ptr[i]`와 `*(ptr+i)` 가 동일한 이유 |
| [struct.cpp](struct.cpp) | 기본 구조체 | `struct` 선언과 멤버 접근(`.`) |
| [struct_ptr.cpp](struct_ptr.cpp) | 구조체 포인터 | 구조체 배열을 포인터로 함수에 전달 |
| [struct_arr.cpp](struct_arr.cpp) | 내부 포인터 멤버 + typedef | 포인터 멤버를 가진 구조체 배열, C 스타일 typedef |
| [struct_func.cpp](struct_func.cpp) | 포인터 매개변수 함수 | 포인터로 원본 값을 함수 안에서 수정 |

---

## 핵심 개념 요약

```cpp
int* ptr = &a;    // ptr은 a의 주소를 저장
*ptr              // 역참조: ptr이 가리키는 값
ptr->member       // == (*ptr).member (구조체 포인터 멤버 접근)

// 배열과 포인터
int arr[] = {1, 2, 3};
int* ptr = arr;
ptr[1] == *(ptr + 1) == arr[1]  // 모두 동일

// 함수에 구조체를 포인터로 전달하는 이유
// → 큰 구조체를 값으로 복사하면 메모리 낭비
void func(Person* p) { ... }
```

> **앞 단계:** [01_basics](../01_basics/)의 참조·포인터 기초를 먼저 보세요.  
> **다음 단계:** [03_classes_oop](../03_classes_oop/)
