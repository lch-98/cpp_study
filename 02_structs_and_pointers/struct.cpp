/*
 * [Topic] Basic Struct
 * 구조체(struct)의 선언과 멤버 접근 기본 예제.
 * 구조체는 서로 연관된 데이터를 하나의 타입으로 묶는 사용자 정의 타입이다.
 *
 * 멤버 접근: 인스턴스.멤버명 (dot operator)
 * 포인터를 통한 접근: ptr->멤버명 (arrow operator)  ← struct_ptr.cpp 참고
 */
#include <iostream>
using namespace std;

struct test
{
    int a;
    int b;
};


int main() {
    test tc;
    tc.a = 1;
    tc.b = 2;

    test tc2;
    tc2.a = 3;
    tc2.b = 4;

    cout << tc.a << " " << tc.b << endl;
    cout << tc2.a << " " << tc2.b << endl;

    return 0;
}
