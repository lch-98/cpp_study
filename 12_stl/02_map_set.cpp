/*
 * [Topic] map, set, unordered_map, unordered_set
 * 정렬 컨테이너(Red-Black Tree)와 해시 컨테이너의 차이.
 *
 * map/set        : 정렬 유지, O(log n) 삽입/탐색
 * unordered_map  : 해시 테이블, 평균 O(1), 정렬 없음
 *
 * Practice:
 *   - 문자열 배열에서 중복을 제거하는 두 가지 방법 비교 (set vs sort+unique)
 *   - unordered_map으로 단어 빈도 카운터 만들기
 */
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

int main() {
    // map — 키 기준 자동 정렬
    map<string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 82;
    scores["Charlie"] = 88;
    scores["Alice"] = 97;  // 덮어쓰기

    for (const auto& [name, score] : scores)  // C++17 구조적 바인딩
        cout << name << ": " << score << "\n";
    cout << "\n";

    // find vs []
    if (scores.count("Bob")) cout << "Bob 있음\n";
    auto it = scores.find("Dave");
    if (it == scores.end()) cout << "Dave 없음\n";
    cout << "\n";

    // set — 중복 없는 정렬된 집합
    set<int> s = {5, 3, 1, 4, 2, 3, 5};  // 중복 자동 제거
    for (int x : s) cout << x << " ";
    cout << "\n\n";

    // unordered_map — 해시 기반, 빠른 탐색
    unordered_map<string, int> freq;
    string words[] = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    for (const auto& w : words) freq[w]++;

    for (const auto& [word, count] : freq)
        cout << word << ": " << count << "\n";

    return 0;
}
