/*
 * [Topic] Memory Leak — 메모리 누수
 * 메모리 누수가 발생하는 패턴과 그 결과를 보여주는 예제.
 *
 * 누수 발생 원인:
 *   1. delete 호출 누락
 *   2. 예외 발생 시 delete에 도달 못 함
 *   3. 포인터 덮어쓰기로 원래 주소 유실
 *
 * Key points:
 *   - 누수는 런타임에 드러나지 않고 장시간 실행 시 메모리 고갈로 나타남
 *   - 실무에서는 스마트 포인터로 구조적으로 방지
 *
 * Practice:
 *   - leak_example 함수를 스마트 포인터로 고쳐보기 (03_unique_ptr.cpp 참고)
 */
#include <iostream>
using namespace std;

void leak_example() {
    int* p = new int(42);
    cout << "값: " << *p << "\n";
    // delete p; 가 없어서 힙에 남음 → 누수
}

void overwrite_example() {
    int* p = new int(10);
    p = new int(20);  // 원래 주소 유실 → 첫 번째 10은 영원히 해제 불가
    cout << "값: " << *p << "\n";
    delete p;  // 두 번째 20만 해제됨
}

void exception_example() {
    int* p = new int(99);
    // throw가 발생하면 delete에 도달하지 못함
    // try { throw runtime_error("오류"); } catch(...) {}
    cout << "값: " << *p << "\n";
    delete p;  // 정상 실행에서만 도달
}

int main() {
    leak_example();
    overwrite_example();
    exception_example();
    cout << "프로그램 종료 (OS가 메모리 회수하지만 장기 실행 시 문제)\n";
    return 0;
}
