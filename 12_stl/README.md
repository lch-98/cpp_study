# 12. STL (표준 템플릿 라이브러리)

STL 컨테이너와 알고리즘을 자유롭게 다루는 것이 실무 C++의 기본이다.

---

## 학습 순서

| 파일 | 주제 | 핵심 키워드 |
|------|------|------------|
| [01_vector.cpp](01_vector.cpp) | 동적 배열 | `push_back`, `emplace_back`, `reserve`, erase-remove |
| [02_map_set.cpp](02_map_set.cpp) | 정렬/해시 컨테이너 | `map`, `set`, `unordered_map`, 구조적 바인딩 |
| [03_stack_queue.cpp](03_stack_queue.cpp) | LIFO/FIFO/힙 | `stack`, `queue`, `priority_queue` |
| [04_iterators.cpp](04_iterators.cpp) | 이터레이터 | `begin/end`, `rbegin`, `advance`, `distance` |
| [05_algorithms.cpp](05_algorithms.cpp) | 표준 알고리즘 | `sort`, `find`, `transform`, `accumulate` |
| [06_lambda.cpp](06_lambda.cpp) | 람다 표현식 | 캡처, 클로저, `function<>`, `mutable` |

---

## 컨테이너 선택 가이드

| 상황 | 컨테이너 |
|------|---------|
| 순서 있는 배열, 랜덤 접근 | `vector` |
| 키-값 쌍, 정렬 필요 | `map` |
| 키-값 쌍, 빠른 탐색 | `unordered_map` |
| 중복 없는 집합 | `set` / `unordered_set` |
| 양쪽 끝 삽입/삭제 | `deque` |
| 중간 삽입/삭제 빈번 | `list` |
| LIFO | `stack` |
| FIFO | `queue` |
| 우선순위 | `priority_queue` |

> **앞 단계:** [11_templates](../11_templates/)
> **다음 단계:** [13_modern_cpp](../13_modern_cpp/)
