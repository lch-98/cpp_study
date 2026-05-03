/*
 * [Topic] STL Algorithms — 표준 알고리즘
 * <algorithm> 헤더의 핵심 알고리즘들.
 * 직접 반복문을 쓰는 것보다 의도가 명확하고 최적화되어 있다.
 *
 * Key points:
 *   - 대부분은 [begin, end) 범위를 받음
 *   - 술어(predicate): 조건을 나타내는 함수/람다
 *   - transform : 변환, accumulate : 누적
 *
 * Practice:
 *   - 벡터에서 최빈값(가장 많이 나온 값) 찾기
 *   - nth_element로 k번째 큰 값 O(n)으로 찾기
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

int main() {
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

    // 정렬
    auto sorted = v;
    sort(sorted.begin(), sorted.end());
    for (int x : sorted) cout << x << " "; cout << "\n";

    // 탐색
    cout << "find(5): " << *find(v.begin(), v.end(), 5) << "\n";
    cout << "count(1): " << count(v.begin(), v.end(), 1) << "\n";
    cout << "min: " << *min_element(v.begin(), v.end()) << "\n";
    cout << "max: " << *max_element(v.begin(), v.end()) << "\n";
    cout << "sum: " << accumulate(v.begin(), v.end(), 0) << "\n\n";

    // 조건 검사
    cout << "all >0: " << all_of(v.begin(), v.end(), [](int x){ return x > 0; }) << "\n";
    cout << "any >8: " << any_of(v.begin(), v.end(), [](int x){ return x > 8; }) << "\n";
    cout << "none <0: " << none_of(v.begin(), v.end(), [](int x){ return x < 0; }) << "\n\n";

    // 변환
    vector<int> doubled(v.size());
    transform(v.begin(), v.end(), doubled.begin(), [](int x){ return x * 2; });
    for (int x : doubled) cout << x << " "; cout << "\n";

    // 문자열 변환
    string s = "Hello World";
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout << s << "\n";

    // 채우기, 생성
    vector<int> filled(5);
    fill(filled.begin(), filled.end(), 7);
    for (int x : filled) cout << x << " "; cout << "\n";

    iota(filled.begin(), filled.end(), 10);  // 10, 11, 12, 13, 14
    for (int x : filled) cout << x << " "; cout << "\n";

    return 0;
}
