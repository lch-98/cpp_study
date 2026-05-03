/*
 * [Topic] std::optional & std::variant (C++17)
 *
 * std::optional<T>:
 *   - 값이 있을 수도 없을 수도 있는 타입
 *   - 실패 가능한 연산의 반환 타입으로 사용 (nullptr, -1 대신)
 *   - has_value(), value(), value_or() 로 접근
 *
 * std::variant<T1, T2, ...>:
 *   - 여러 타입 중 하나를 안전하게 저장하는 타입-안전 union
 *   - get<T>(), get_if<T>(), visit() 으로 접근
 *
 * Practice:
 *   - optional을 반환하는 find_in_map 함수 만들기
 *   - variant + visit으로 간단한 계산기 구현
 */
#include <iostream>
#include <optional>
#include <variant>
#include <string>
#include <vector>
using namespace std;

// optional 사용: 실패 가능한 파싱
optional<int> parse_int(const string& s) {
    try {
        return stoi(s);
    } catch (...) {
        return nullopt;  // 값 없음
    }
}

optional<double> safe_divide(double a, double b) {
    if (b == 0) return nullopt;
    return a / b;
}

// variant 사용: 다양한 타입의 값
using Value = variant<int, double, string, bool>;

void print_value(const Value& v) {
    visit([](const auto& val) {
        cout << val << " (type: " << typeid(val).name() << ")\n";
    }, v);
}

int main() {
    // optional 기본
    auto r1 = parse_int("42");
    auto r2 = parse_int("abc");

    if (r1) cout << "파싱 성공: " << *r1 << "\n";
    if (!r2) cout << "파싱 실패\n";

    // value_or: 기본값 제공
    cout << r2.value_or(-1) << "\n";

    // safe_divide
    auto result = safe_divide(10, 3);
    cout << "10/3 = " << result.value_or(0) << "\n";
    result = safe_divide(10, 0);
    cout << "10/0 = " << result.value_or(0) << " (failed)\n\n";

    // variant 기본
    Value v1 = 42;
    Value v2 = 3.14;
    Value v3 = string("hello");
    Value v4 = true;

    print_value(v1);
    print_value(v2);
    print_value(v3);
    print_value(v4);

    // 타입 확인
    if (holds_alternative<int>(v1)) cout << "v1은 int\n";

    // 값 변경
    v1 = string("changed");
    print_value(v1);

    // vector<variant>: 다형성 없이 여러 타입 저장
    vector<Value> mixed = {1, 2.5, string("three"), false};
    for (const auto& val : mixed) print_value(val);

    return 0;
}
