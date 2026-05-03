/*
 * [Topic] Range-based for & Structured Bindings (C++11/17)
 * 더 읽기 좋은 순회와 분해 문법.
 *
 * range-based for:
 *   for (auto x : container)    — 값 복사 (수정 불가)
 *   for (auto& x : container)   — 참조 (수정 가능)
 *   for (const auto& x : container) — const 참조 (읽기 전용, 효율적)
 *
 * structured bindings (C++17):
 *   auto [a, b] = pair;
 *   auto [key, val] = map_entry;
 *   auto [x, y, z] = array;
 *
 * Practice:
 *   - 2D vector를 range-for로 순회하며 최댓값 찾기
 *   - tuple<string, int, double>을 구조적 바인딩으로 분해하기
 */
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <array>
using namespace std;

struct Point3D { double x, y, z; };

int main() {
    // range-based for 기본
    vector<int> v = {1, 2, 3, 4, 5};
    for (const auto& x : v) cout << x << " ";
    cout << "\n";

    // 참조로 수정
    for (auto& x : v) x *= 2;
    for (auto x : v) cout << x << " ";
    cout << "\n\n";

    // 구조적 바인딩 — pair
    auto p = make_pair("hello", 42);
    auto [str, num] = p;
    cout << str << ", " << num << "\n";

    // 구조적 바인딩 — map
    map<string, int> scores = {{"Alice", 95}, {"Bob", 82}, {"Charlie", 88}};
    for (const auto& [name, score] : scores)
        cout << name << ": " << score << "\n";
    cout << "\n";

    // 구조적 바인딩 — array
    array<int, 3> arr = {10, 20, 30};
    auto [a, b, c] = arr;
    cout << a << " " << b << " " << c << "\n";

    // 구조적 바인딩 — tuple
    tuple<string, int, double> t = {"cpp", 17, 3.14};
    auto [lang, ver, pi] = t;
    cout << lang << " " << ver << " " << pi << "\n";

    // 함수 반환값 분해
    auto minmax = [](const vector<int>& v) -> pair<int,int> {
        int mn = v[0], mx = v[0];
        for (int x : v) { mn = min(mn, x); mx = max(mx, x); }
        return {mn, mx};
    };
    auto [mn, mx] = minmax(v);
    cout << "min=" << mn << " max=" << mx << "\n";

    return 0;
}
