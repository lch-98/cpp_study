/*
 * [Topic] shared_ptr — 공유 소유권 스마트 포인터
 * 여러 포인터가 하나의 자원을 공유하며, 마지막 소유자가 사라질 때 해제된다.
 * 내부적으로 참조 카운트(reference count)를 유지한다.
 *
 * Key points:
 *   - make_shared<T>() : 권장 생성 방법 (카운트 블록 + 객체 한 번에 할당)
 *   - use_count() : 현재 공유 소유자 수
 *   - 복사 시 카운트 증가, 소멸 시 카운트 감소
 *   - 카운트가 0이 되면 자동 delete
 *
 * Practice:
 *   - 두 shared_ptr이 서로를 참조하면 카운트가 0이 되지 않아 누수 발생
 *     → 05_weak_ptr.cpp 에서 해결
 */
#include <iostream>
#include <memory>
using namespace std;

struct Node {
    int val;
    Node(int v) : val(v) { cout << "Node(" << v << ") 생성\n"; }
    ~Node() { cout << "Node(" << val << ") 소멸\n"; }
};

void print_count(const shared_ptr<Node>& p, const string& label) {
    cout << label << " use_count: " << p.use_count() << "\n";
}

int main() {
    auto p1 = make_shared<Node>(10);
    print_count(p1, "p1 생성 후");

    {
        auto p2 = p1;  // 공유 — 카운트 2
        print_count(p1, "p2 생성 후");
        p2->val = 20;
        cout << "p1->val (p2로 수정): " << p1->val << "\n";
    }  // p2 소멸 — 카운트 1
    print_count(p1, "p2 소멸 후");

    // 함수에 shared_ptr 전달 (복사)
    auto func = [](shared_ptr<Node> p) {
        print_count(p, "  함수 내");
    };
    func(p1);  // 함수 안에서 카운트 2, 나오면 1
    print_count(p1, "함수 반환 후");

    return 0;  // p1 소멸 → 카운트 0 → Node 자동 delete
}
