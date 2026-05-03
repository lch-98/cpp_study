/*
 * [Topic] constexpr — 컴파일 타임 계산
 * constexpr: 컴파일 타임에 값을 확정할 수 있음을 나타냄.
 *
 * const vs constexpr:
 *   const      : 런타임 상수도 가능 (초기화가 런타임 값일 수 있음)
 *   constexpr  : 반드시 컴파일 타임 상수
 *
 * constexpr 함수:
 *   - 컴파일 타임 인자라면 컴파일 타임에 실행
 *   - 런타임 인자도 받을 수 있음 (그러면 런타임 실행)
 *
 * if constexpr (C++17):
 *   - 컴파일 타임 조건 분기 (템플릿 분기에 유용)
 *
 * Practice:
 *   - constexpr로 피보나치 수열 계산기 만들기
 *   - if constexpr로 타입별 다른 동작을 하는 함수 만들기
 */
#include <iostream>
#include <type_traits>
using namespace std;

constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr double PI = 3.14159265358979;

constexpr double circle_area(double r) {
    return PI * r * r;
}

// if constexpr — 타입에 따른 컴파일 타임 분기
template<typename T>
void describe(T val) {
    if constexpr (is_integral_v<T>) {
        cout << val << " (정수형, " << sizeof(T) * 8 << "bit)\n";
    } else if constexpr (is_floating_point_v<T>) {
        cout << val << " (부동소수점)\n";
    } else {
        cout << val << " (기타 타입)\n";
    }
}

// constexpr 클래스 (C++14)
class ConstPoint {
public:
    constexpr ConstPoint(int x, int y) : x_(x), y_(y) {}
    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }
    constexpr int dist_sq() const { return x_*x_ + y_*y_; }
private:
    int x_, y_;
};

int main() {
    // 컴파일 타임 계산 (배열 크기 등에 사용 가능)
    constexpr int f5 = factorial(5);    // 컴파일 타임
    constexpr double area = circle_area(5.0);  // 컴파일 타임

    cout << "5! = " << f5 << "\n";
    cout << "반지름 5 원의 넓이: " << area << "\n";

    // 런타임 인자로도 호출 가능
    int n;
    cin >> n;
    cout << n << "! = " << factorial(n) << "\n";  // 런타임

    // if constexpr
    describe(42);
    describe(3.14);
    describe("hello");

    // constexpr 클래스
    constexpr ConstPoint p(3, 4);
    static_assert(p.dist_sq() == 25, "컴파일 타임 검증");
    cout << "(" << p.x() << ", " << p.y() << ") dist²=" << p.dist_sq() << "\n";

    return 0;
}
