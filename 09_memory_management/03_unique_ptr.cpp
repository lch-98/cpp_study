/*
 * [Topic] unique_ptr — 단독 소유권 스마트 포인터
 * unique_ptr은 하나의 자원을 하나의 포인터만 소유한다.
 * 스코프를 벗어나거나 명시적으로 해제하면 자동으로 delete된다.
 *
 * Key points:
 *   - make_unique<T>() : C++14, 권장하는 생성 방법
 *   - 복사 불가 (소유권은 하나), 이동(move)만 가능
 *   - get()    : raw pointer 얻기 (소유권 이전 없음)
 *   - reset()  : 해제 후 nullptr
 *   - release(): 소유권 포기, raw pointer 반환
 *
 * Practice:
 *   - unique_ptr을 복사하려 하면 어떤 컴파일 에러가 나는지 확인
 *   - 함수 인자로 unique_ptr을 넘기는 세 가지 방법 조사 (by value, by ref, raw ptr)
 */
#include <iostream>
#include <memory>
using namespace std;

struct Resource {
    string name;
    Resource(string n) : name(n) { cout << name << " 생성\n"; }
    ~Resource() { cout << name << " 소멸\n"; }
    void use() { cout << name << " 사용 중\n"; }
};

void take_ownership(unique_ptr<Resource> res) {
    res->use();
    // 함수 종료 시 res 소멸 → Resource 자동 delete
}

int main() {
    // 생성
    auto r1 = make_unique<Resource>("R1");
    r1->use();

    // 이동 (소유권 이전)
    auto r2 = move(r1);  // r1은 이제 nullptr
    if (!r1) cout << "r1은 nullptr\n";
    r2->use();

    // 함수로 소유권 이전
    take_ownership(move(r2));
    if (!r2) cout << "r2도 nullptr\n";

    // 배열
    auto arr = make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) arr[i] = i;
    cout << "arr[2] = " << arr[2] << "\n";

    // 스코프로 조기 해제
    {
        auto r3 = make_unique<Resource>("R3");
    }  // 여기서 R3 소멸
    cout << "스코프 종료 후\n";

    return 0;
}
