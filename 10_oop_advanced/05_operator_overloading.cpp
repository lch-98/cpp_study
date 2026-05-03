/*
 * [Topic] Operator Overloading — 연산자 오버로딩
 * 사용자 정의 타입에 +, ==, <<, [] 등의 연산자를 정의한다.
 *
 * Key points:
 *   - operator+ : 새 객체 반환 (원본 수정 없음)
 *   - operator+= : *this 수정 후 반환
 *   - operator== : bool 반환
 *   - operator<< : ostream& 반환 (연쇄 출력용)
 *   - friend 함수: private 멤버에 접근 가능한 비멤버 함수
 *
 * 오버로딩 불가 연산자: :: . .* ?: sizeof
 *
 * Practice:
 *   - Vec2에 operator* (스칼라 곱), operator[] 추가해보기
 *   - operator< 추가해서 vector<Vec2>를 sort 해보기
 */
#include <iostream>
#include <cmath>
using namespace std;

class Vec2 {
public:
    double x, y;
    Vec2(double x = 0, double y = 0) : x(x), y(y) {}

    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }

    bool operator==(const Vec2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vec2& o) const { return !(*this == o); }

    double length() const { return sqrt(x * x + y * y); }

    // friend: ostream에 Vec2 출력
    friend ostream& operator<<(ostream& os, const Vec2& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

int main() {
    Vec2 a(1, 2), b(3, 4);

    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "a + b = " << a + b << "\n";
    cout << "a - b = " << a - b << "\n";

    a += b;
    cout << "a += b → a = " << a << "\n";

    cout << "a == b: " << (a == b) << "\n";
    cout << "|b| = " << b.length() << "\n";

    return 0;
}
