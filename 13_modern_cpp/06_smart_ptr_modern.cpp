/*
 * [Topic] Modern Smart Pointer Usage
 * 실무에서 스마트 포인터를 올바르게 사용하는 패턴 모음.
 *
 * 핵심 규칙:
 *   - make_unique / make_shared 를 항상 사용 (new 직접 사용 금지)
 *   - unique_ptr이 기본 선택, 공유가 필요할 때만 shared_ptr
 *   - 함수 인자: 소유권 이전 = unique_ptr by value, 단순 사용 = raw ptr 또는 ref
 *   - 반환값: 팩토리 함수는 unique_ptr 반환
 *
 * Practice:
 *   - unique_ptr<Shape>를 반환하는 팩토리 함수 완성해보기
 *   - shared_ptr 기반 캐시 구현해보기 (key → weak_ptr 저장)
 */
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
using namespace std;

class Widget {
    string name;
public:
    Widget(string n) : name(n) { cout << name << " 생성\n"; }
    ~Widget() { cout << name << " 소멸\n"; }
    void use() const { cout << name << " 사용\n"; }
    const string& getName() const { return name; }
};

// 팩토리 함수 패턴 (unique_ptr 반환)
unique_ptr<Widget> createWidget(const string& name) {
    return make_unique<Widget>(name);
}

// 소유권 없이 사용 — raw pointer 또는 const ref
void use_widget(const Widget* w) {
    if (w) w->use();
}
void use_widget_ref(const Widget& w) {
    w.use();
}

// 소유권 이전 받기
void take_widget(unique_ptr<Widget> w) {
    w->use();
}  // 함수 종료 시 자동 소멸

int main() {
    cout << "=== 팩토리 패턴 ===\n";
    auto w1 = createWidget("W1");
    use_widget(w1.get());        // 소유권 이전 없이 사용
    use_widget_ref(*w1);

    cout << "\n=== 소유권 이전 ===\n";
    take_widget(move(w1));       // w1은 nullptr
    cout << "w1 is " << (w1 ? "valid" : "null") << "\n";

    cout << "\n=== 컨테이너 ===\n";
    vector<unique_ptr<Widget>> widgets;
    widgets.push_back(createWidget("A"));
    widgets.push_back(createWidget("B"));
    widgets.push_back(createWidget("C"));
    for (const auto& w : widgets) w->use();

    cout << "\n=== 소멸 ===\n";
    return 0;
}
