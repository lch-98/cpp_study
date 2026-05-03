/*
 * [Topic] Lambda Expression — 람다 표현식
 * 이름 없는 함수 객체. C++11~
 *
 * 문법: [캡처](매개변수) -> 반환타입 { 본문 }
 *
 * 캡처:
 *   []       : 캡처 없음
 *   [=]      : 외부 변수 값으로 캡처 (복사)
 *   [&]      : 외부 변수 참조로 캡처
 *   [x, &y]  : x는 값, y는 참조
 *   [this]   : 멤버 함수 안에서 this 캡처
 *
 * Practice:
 *   - 람다를 변수에 저장해서 여러 번 호출해보기
 *   - 람다를 반환하는 함수(클로저 팩토리) 만들기
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 람다를 매개변수로 받는 함수
void apply(vector<int>& v, function<int(int)> f) {
    for (auto& x : v) x = f(x);
}

// 람다를 반환하는 함수 (클로저)
auto make_adder(int n) {
    return [n](int x) { return x + n; };  // n을 값으로 캡처
}

auto make_counter() {
    int count = 0;
    return [count]() mutable {  // mutable: 캡처 값 수정 가능
        return ++count;
    };
}

int main() {
    // 기본 람다
    auto greet = [](const string& name) {
        cout << "Hello, " << name << "!\n";
    };
    greet("World");

    // 캡처
    int threshold = 5;
    vector<int> v = {1, 7, 3, 8, 2, 9, 4, 6};

    auto big = count_if(v.begin(), v.end(),
        [threshold](int x) { return x > threshold; });
    cout << threshold << " 초과: " << big << "개\n";

    // 참조 캡처로 외부 값 수정
    int total = 0;
    for_each(v.begin(), v.end(), [&total](int x) { total += x; });
    cout << "합계: " << total << "\n";

    // 정렬에 활용
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // 내림차순
    for (int x : v) cout << x << " "; cout << "\n";

    // 클로저
    auto add5 = make_adder(5);
    auto add10 = make_adder(10);
    cout << "add5(3) = " << add5(3) << "\n";
    cout << "add10(3) = " << add10(3) << "\n";

    // mutable 캡처
    auto counter = make_counter();
    cout << counter() << " " << counter() << " " << counter() << "\n";

    // apply 함수에 람다 전달
    vector<int> nums = {1, 2, 3, 4, 5};
    apply(nums, [](int x) { return x * x; });
    for (int x : nums) cout << x << " "; cout << "\n";

    return 0;
}
