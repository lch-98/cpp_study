/*
 * [Topic] auto & decltype — 타입 추론
 * 컴파일러가 타입을 자동으로 추론한다. C++11~
 *
 * auto     : 초기화 표현식에서 타입 추론
 * decltype : 표현식의 타입을 그대로 가져옴 (평가 없이)
 *
 * Key points:
 *   - auto는 const, &를 추론하지 않으므로 명시가 필요할 수 있음
 *   - auto& : 참조로 추론
 *   - const auto& : const 참조 (불필요한 복사 방지)
 *   - decltype(auto) : 반환 타입 추론 (참조도 유지)
 *
 * Practice:
 *   - 람다 반환 타입을 decltype으로 추론해보기
 *   - auto와 auto&의 차이를 vector 수정 예시로 확인
 */
#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
using namespace std;

// 반환 타입 추론 (C++14)
auto add(int a, int b) { return a + b; }

// trailing return type (C++11)
auto multiply(double a, double b) -> double { return a * b; }

// decltype으로 반환 타입 결정
template<typename T, typename U>
auto max_val(T a, U b) -> decltype(a > b ? a : b) {
    return a > b ? a : b;
}

int main() {
    // 기본 auto 추론
    auto i = 42;          // int
    auto d = 3.14;        // double
    auto s = string("hi"); // string
    auto b = true;        // bool

    cout << typeid(i).name() << "\n";  // int
    cout << typeid(d).name() << "\n";  // double

    // const auto& — 복사 없이 읽기 (map 순회의 올바른 방법)
    map<string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}};
    for (const auto& [key, val] : m)  // 구조적 바인딩 + const auto&
        cout << key << "=" << val << " ";
    cout << "\n";

    // auto&로 수정
    vector<int> v = {1, 2, 3, 4, 5};
    for (auto& x : v) x *= 2;  // 참조로 수정
    for (auto x : v) cout << x << " ";  // 값 복사로 읽기
    cout << "\n";

    // decltype
    int x = 10;
    decltype(x) y = 20;      // int
    decltype(x + 1.0) z = 0; // double (표현식 타입)
    cout << typeid(z).name() << "\n";

    // 함수 사용
    cout << add(3, 4) << "\n";
    cout << multiply(2.5, 4.0) << "\n";
    cout << max_val(3, 4.5) << "\n";

    return 0;
}
