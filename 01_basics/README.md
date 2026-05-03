# 01. Basics (기본 활용)

C++ 입문에서 가장 먼저 익혀야 할 핵심 개념들을 다룹니다.

---

## 학습 순서

### [01_io](01_io/) — 입출력
| 파일 | 설명 |
|------|------|
| [output.cpp](01_io/output.cpp) | `cout`으로 콘솔 출력 |
| [input.cpp](01_io/input.cpp) | `cin`으로 사용자 입력 받기 |

### [02_variables](02_variables/) — 변수 & 메모리
| 파일 | 설명 |
|------|------|
| [reference_pointer.cpp](02_variables/reference_pointer.cpp) | 참조자(reference)와 포인터(pointer) 차이 비교 |
| [value_reference_pointer.cpp](02_variables/value_reference_pointer.cpp) | 함수 인자 전달 방식: 값 / 참조 / 포인터 |
| [static_const.cpp](02_variables/static_const.cpp) | static 지역 변수와 const 포인터 |
| [volatile_const.cpp](02_variables/volatile_const.cpp) | const(상수화)와 volatile(최적화 억제) |

### [03_operators](03_operators/) — 연산자
| 파일 | 설명 |
|------|------|
| [a++_++a.cpp](03_operators/a++_++a.cpp) | 후위(a++)와 전위(++a) 연산자 차이 |

### [04_project_structure](04_project_structure/) — CMake 프로젝트 구조
| 파일 | 설명 |
|------|------|
| [include/Robot.h](04_project_structure/include/Robot.h) | 클래스 선언 헤더 (`#pragma once`) |
| [src/utils/Robot.cpp](04_project_structure/src/utils/Robot.cpp) | 클래스 구현부 |
| [src/main.cpp](04_project_structure/src/main.cpp) | 진입점 (CMake 빌드 예시) |

**빌드 방법:**
```bash
cd 04_project_structure
mkdir build && cd build
cmake .. && cmake --build .
```

---

## 핵심 개념 요약

```
참조자(ref)    → NULL 불가, 재할당 불가, 같은 주소 공유
포인터(ptr)    → NULL 가능, 재할당 가능, * 로 역참조
값 전달        → 복사본 수정, 원본 불변
참조/포인터 전달 → 원본 직접 수정 가능
static 변수    → 함수 종료 후에도 값 유지
const 포인터   → 가리키는 값 변경 불가 (주소 변경은 가능)
```
