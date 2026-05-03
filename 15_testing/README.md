# 15. Testing (단위 테스트)

자동화 테스트는 코드 변경 시 기존 기능이 깨지지 않았음을 빠르게 확인한다.

---

## 학습 순서

| 파일 | 주제 |
|------|------|
| [01_gtest_basic.cpp](01_gtest_basic.cpp) | 기본 assert 매크로, 단위 테스트 작성 |
| [02_test_fixtures.cpp](02_test_fixtures.cpp) | 픽스처, TDD 사이클 |

---

## Google Test 설치 (vcpkg)

```bash
vcpkg install gtest
```

CMakeLists.txt:
```cmake
find_package(GTest CONFIG REQUIRED)
target_link_libraries(target PRIVATE GTest::gtest GTest::gtest_main)
```

---

## TDD 사이클

```
1. Red    → 실패하는 테스트 먼저 작성
2. Green  → 통과하는 최소한의 코드 작성
3. Refactor → 코드 정리 (테스트는 계속 통과)
```

## 핵심 매크로

```cpp
EXPECT_EQ(a, b)         // a == b
EXPECT_NE(a, b)         // a != b
EXPECT_TRUE(cond)       // cond == true
EXPECT_NEAR(a, b, eps)  // |a-b| < eps
EXPECT_THROW(expr, exc) // expr이 exc 예외 발생
ASSERT_*                // 실패 시 즉시 중단
```

> **앞 단계:** [14_file_io](../14_file_io/)
> **다음 단계:** [16_design_patterns](../16_design_patterns/)
