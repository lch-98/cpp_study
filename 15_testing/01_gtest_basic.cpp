/*
 * [Topic] Google Test — 기본 사용법
 * 자동화된 단위 테스트로 코드 정확성을 검증한다.
 *
 * 설치: vcpkg install gtest
 * CMake:
 *   find_package(GTest CONFIG REQUIRED)
 *   target_link_libraries(target PRIVATE GTest::gtest GTest::gtest_main)
 *
 * 주요 매크로:
 *   TEST(Suite, Name)    : 테스트 케이스 정의
 *   EXPECT_EQ(a, b)      : a == b 검증 (실패해도 계속)
 *   ASSERT_EQ(a, b)      : a == b 검증 (실패하면 즉시 중단)
 *   EXPECT_TRUE/FALSE    : bool 조건 검증
 *   EXPECT_THROW         : 예외 발생 검증
 *   EXPECT_NEAR(a, b, e) : 부동소수점 근사 비교
 *
 * Practice:
 *   - binary_search 함수에 대한 테스트 5개 이상 작성하기
 *   - 경계값(edge case) 테스트: 빈 배열, 단일 원소, 찾지 못한 경우
 */

// gtest 없는 환경을 위한 수동 테스트 프레임워크 예시
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
using namespace std;

// ===== 테스트할 코드 =====
int add(int a, int b) { return a + b; }
double divide(double a, double b) {
    if (b == 0) throw invalid_argument("division by zero");
    return a / b;
}
int binary_search(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ===== 수동 테스트 (gtest 대체) =====
int pass_count = 0, fail_count = 0;

#define EXPECT_EQ(a, b) do { \
    if ((a) == (b)) { cout << "  PASS\n"; pass_count++; } \
    else { cout << "  FAIL: " << (a) << " != " << (b) << " (line " << __LINE__ << ")\n"; fail_count++; } \
} while(0)

#define EXPECT_NEAR(a, b, eps) do { \
    if (abs((a)-(b)) < (eps)) { cout << "  PASS\n"; pass_count++; } \
    else { cout << "  FAIL: |" << (a) << " - " << (b) << "| >= " << (eps) << "\n"; fail_count++; } \
} while(0)

#define EXPECT_THROW(expr, exc) do { \
    try { expr; cout << "  FAIL: 예외 없음\n"; fail_count++; } \
    catch (const exc&) { cout << "  PASS\n"; pass_count++; } \
    catch (...) { cout << "  FAIL: 다른 예외\n"; fail_count++; } \
} while(0)

void test_add() {
    cout << "[add 테스트]\n";
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(0, 0), 0);
    EXPECT_EQ(add(100, -50), 50);
}

void test_divide() {
    cout << "[divide 테스트]\n";
    EXPECT_NEAR(divide(10, 3), 3.333, 0.001);
    EXPECT_NEAR(divide(1, 4), 0.25, 0.0001);
    EXPECT_THROW(divide(1, 0), invalid_argument);
}

void test_binary_search() {
    cout << "[binary_search 테스트]\n";
    vector<int> v = {1, 3, 5, 7, 9, 11, 13};
    EXPECT_EQ(binary_search(v, 7), 3);
    EXPECT_EQ(binary_search(v, 1), 0);
    EXPECT_EQ(binary_search(v, 13), 6);
    EXPECT_EQ(binary_search(v, 99), -1);
    EXPECT_EQ(binary_search(v, 0), -1);
    vector<int> single = {42};
    EXPECT_EQ(binary_search(single, 42), 0);
}

int main() {
    test_add();
    test_divide();
    test_binary_search();
    cout << "\n결과: " << pass_count << " passed, " << fail_count << " failed\n";
    return fail_count > 0 ? 1 : 0;
}

/* === gtest 사용 시 실제 코드 ===
#include <gtest/gtest.h>
TEST(AddTest, BasicCases) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(-1, 1), 0);
}
TEST(DivideTest, DivisionByZero) {
    EXPECT_THROW(divide(1, 0), invalid_argument);
}
// main은 gtest_main이 제공하므로 불필요
*/
