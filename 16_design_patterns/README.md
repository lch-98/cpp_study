# 16. Design Patterns (디자인 패턴)

반복되는 설계 문제의 표준 해법. 코드의 의도를 명확히 하고 변경에 강한 구조를 만든다.

---

## 학습 순서

| 파일 | 패턴 | 카테고리 |
|------|------|---------|
| [01_singleton.cpp](01_singleton.cpp) | 싱글톤 | 생성 |
| [02_factory.cpp](02_factory.cpp) | 팩토리 (등록 기반) | 생성 |
| [03_observer.cpp](03_observer.cpp) | 옵저버 (이벤트 버스) | 행동 |
| [04_strategy.cpp](04_strategy.cpp) | 전략 | 행동 |

---

## 패턴 선택 가이드

```
인스턴스 하나만 필요    → Singleton
종류에 따라 생성 다름  → Factory
변화를 여러 곳에 전파  → Observer
알고리즘을 교체 가능   → Strategy
```

> **앞 단계:** [15_testing](../15_testing/)
> **다음 단계:** [17_async](../17_async/)
