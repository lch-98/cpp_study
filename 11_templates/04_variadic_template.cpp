/*
 * [Topic] Variadic Template — 가변 인자 템플릿
 * 임의 개수의 타입/값 인자를 받는 템플릿. C++11~
 *
 * sizeof...(Args) : 팩의 인자 수
 * 재귀 방식과 fold expression(C++17) 두 가지 방법 모두 소개.
 *
 * Practice:
 *   - max_of(1, 5, 3, 2, 4) 처럼 여러 값 중 최댓값 반환하는 함수 만들기
 *   - TypeList<int, double, string>의 각 타입 이름을 출력해보기
 */
#include <iostream>
#include <string>
using namespace std;

// 재귀 종료 조건
void print() { cout << "\n"; }

// 가변 인자 재귀
template<typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first;
    if (sizeof...(rest) > 0) cout << ", ";
    print(rest...);
}

// C++17 fold expression — 더 간결
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // 모든 인자를 + 로 접기
}

template<typename... Args>
void print_all(Args... args) {
    ((cout << args << " "), ...);  // 쉼표 연산자 fold
    cout << "\n";
}

// 타입 개수 세기
template<typename... Args>
constexpr size_t type_count() { return sizeof...(Args); }

int main() {
    print(1, 2.5, "hello", 'A');
    print("only one");

    cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    cout << "sum(1.1, 2.2, 3.3) = " << sum(1.1, 2.2, 3.3) << "\n";

    print_all(10, 20.5, "cpp", true);

    cout << "타입 수: " << type_count<int, double, string>() << "\n";

    return 0;
}
