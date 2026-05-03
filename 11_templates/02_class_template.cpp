/*
 * [Topic] Class Template — 클래스 템플릿
 * 타입에 독립적인 제네릭 클래스. STL의 vector, map 등이 모두 클래스 템플릿이다.
 *
 * Key points:
 *   - 멤버 함수도 템플릿 매개변수를 사용
 *   - 클래스 외부에서 정의 시 template<typename T> 반복 필요
 *   - 기본 타입 매개변수 지정 가능
 *
 * Practice:
 *   - Stack<T>에 peek() (top 확인만, pop 없이) 추가해보기
 *   - Stack<T, size_t MaxSize>로 최대 크기를 제한하는 버전 만들기
 */
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// 제네릭 Stack
template<typename T>
class Stack {
    vector<T> data;
public:
    void push(const T& val) { data.push_back(val); }

    T pop() {
        if (empty()) throw underflow_error("Stack이 비어있음");
        T top = data.back();
        data.pop_back();
        return top;
    }

    const T& top() const {
        if (empty()) throw underflow_error("Stack이 비어있음");
        return data.back();
    }

    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }

    void print() const {
        cout << "Stack [";
        for (size_t i = 0; i < data.size(); i++) {
            cout << data[i];
            if (i + 1 < data.size()) cout << ", ";
        }
        cout << "]\n";
    }
};

// 기본 타입 매개변수
template<typename Key, typename Value = string>
class SimpleMap {
    vector<pair<Key, Value>> entries;
public:
    void set(const Key& k, const Value& v) {
        for (auto& e : entries)
            if (e.first == k) { e.second = v; return; }
        entries.push_back({k, v});
    }
    Value get(const Key& k) const {
        for (const auto& e : entries)
            if (e.first == k) return e.second;
        throw out_of_range("키 없음");
    }
};

int main() {
    Stack<int> si;
    si.push(1); si.push(2); si.push(3);
    si.print();
    cout << "pop: " << si.pop() << "\n";
    si.print();

    Stack<string> ss;
    ss.push("hello"); ss.push("world");
    ss.print();

    SimpleMap<int> m;
    m.set(1, "one"); m.set(2, "two");
    cout << m.get(1) << ", " << m.get(2) << "\n";

    return 0;
}
