/*
 * [Topic] weak_ptr — 순환 참조 해결
 * shared_ptr의 순환 참조 문제를 weak_ptr로 해결하는 예제.
 *
 * 순환 참조:
 *   A → B, B → A 를 shared_ptr로 연결하면
 *   둘 다 카운트가 0이 되지 않아 영원히 소멸되지 않음 → 메모리 누수
 *
 * weak_ptr:
 *   - 참조 카운트를 증가시키지 않음
 *   - lock()으로 임시 shared_ptr 획득 후 사용
 *   - expired()로 가리키는 객체가 살아있는지 확인
 *
 * Practice:
 *   - weak_ptr을 shared_ptr로 바꾼 뒤 소멸자가 호출되지 않음을 확인
 */
#include <iostream>
#include <memory>
using namespace std;

struct B;  // 전방 선언

struct A {
    shared_ptr<B> b_ptr;
    ~A() { cout << "A 소멸\n"; }
};

struct B {
    weak_ptr<A> a_ptr;  // shared_ptr<A>로 바꾸면 순환 참조 발생
    ~B() { cout << "B 소멸\n"; }
};

int main() {
    cout << "=== 순환 참조 없는 버전 (weak_ptr) ===\n";
    {
        auto a = make_shared<A>();
        auto b = make_shared<B>();
        a->b_ptr = b;
        b->a_ptr = a;  // weak_ptr이므로 카운트 증가 없음
        cout << "a use_count: " << a.use_count() << "\n";
        cout << "b use_count: " << b.use_count() << "\n";
    }  // a, b 모두 정상 소멸
    cout << "스코프 종료\n\n";

    // weak_ptr 사용법
    auto shared = make_shared<int>(42);
    weak_ptr<int> weak = shared;

    if (auto locked = weak.lock()) {
        cout << "weak_ptr 통해 접근: " << *locked << "\n";
    }

    shared.reset();  // 원본 해제
    cout << "expired: " << weak.expired() << "\n";  // 1 (true)

    return 0;
}
