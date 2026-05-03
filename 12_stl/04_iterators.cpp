/*
 * [Topic] Iterators — 이터레이터
 * 컨테이너를 순회하는 통일된 인터페이스.
 * 알고리즘 함수들은 이터레이터를 통해 모든 컨테이너에 동작한다.
 *
 * 이터레이터 종류:
 *   - input/output   : 한 번 읽기/쓰기
 *   - forward        : 앞으로만 이동
 *   - bidirectional  : 앞뒤 이동 (list, map)
 *   - random access  : 임의 접근 (vector, deque)
 *
 * Practice:
 *   - reverse_iterator로 vector를 역순으로 출력하기
 *   - iota로 1~10 채운 vector를 만들고 짝수만 출력하기
 */
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <numeric>
#include <iterator>
using namespace std;

int main() {
    vector<int> v(10);
    iota(v.begin(), v.end(), 1);  // 1~10 채우기

    // 정방향 이터레이터
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // 역방향 이터레이터
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        cout << *it << " ";
    cout << "\n";

    // advance, distance
    auto it = v.begin();
    advance(it, 4);  // 5번째 원소
    cout << "5번째: " << *it << "\n";
    cout << "거리: " << distance(v.begin(), it) << "\n";

    // list는 bidirectional (random access 불가)
    list<int> lst = {10, 20, 30, 40, 50};
    auto lit = lst.begin();
    advance(lit, 2);
    cout << "list 3번째: " << *lit << "\n";
    --lit;  // 뒤로도 이동 가능
    cout << "list 2번째: " << *lit << "\n";

    // map 이터레이터
    map<string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}};
    for (auto it = m.begin(); it != m.end(); ++it)
        cout << it->first << ":" << it->second << " ";
    cout << "\n";

    // ostream_iterator (출력 이터레이터)
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "-"));
    cout << "\n";

    return 0;
}
