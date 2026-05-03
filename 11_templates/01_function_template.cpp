/*
 * [Topic] Function Template — 함수 템플릿
 * 타입에 독립적인 제네릭 함수를 작성한다.
 * 컴파일러가 호출 시점의 타입을 보고 구체적인 함수를 자동 생성한다.
 *
 * Key points:
 *   - template<typename T> : T는 호출 시 결정되는 타입 매개변수
 *   - 명시적 특수화 : 특정 타입에 다른 동작을 정의
 *   - 타입 추론 : 인자에서 T를 자동으로 추론
 *   - 여러 타입 매개변수 : template<typename T, typename U>
 *
 * Practice:
 *   - clamp<T>(val, min, max) 함수 템플릿 직접 작성해보기
 *   - T가 string일 때만 다르게 동작하는 특수화 추가해보기
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 기본 함수 템플릿
template<typename T>
T max_val(T a, T b) {
    return (a > b) ? a : b;
}

// 두 타입 매개변수
template<typename T, typename U>
void print_pair(T a, U b) {
    cout << "(" << a << ", " << b << ")\n";
}

// 명시적 특수화 (const char* 비교 특수화)
template<>
const char* max_val<const char*>(const char* a, const char* b) {
    return (string(a) > string(b)) ? a : b;
}

// 컨테이너를 받는 템플릿
template<typename Container>
typename Container::value_type sum(const Container& c) {
    typename Container::value_type result = 0;
    for (const auto& v : c) result += v;
    return result;
}

// 비타입 템플릿 매개변수
template<int N>
void print_n_times(const string& msg) {
    for (int i = 0; i < N; i++) cout << msg << "\n";
}

int main() {
    cout << max_val(3, 5) << "\n";           // int
    cout << max_val(3.14, 2.71) << "\n";     // double
    cout << max_val(string("abc"), string("xyz")) << "\n";  // string
    cout << max_val("banana", "apple") << "\n";  // 특수화

    print_pair(42, "hello");
    print_pair(3.14, true);

    vector<int> v = {1, 2, 3, 4, 5};
    cout << "sum: " << sum(v) << "\n";

    print_n_times<3>("반복");

    return 0;
}
