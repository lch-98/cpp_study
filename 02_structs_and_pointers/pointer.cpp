/*
 * [Topic] Basic Pointer
 * 포인터의 기본 선언과 역참조(*) 사용법.
 *
 *   int* ptr = &a : ptr은 a의 메모리 주소를 저장
 *   *ptr          : ptr이 가리키는 주소의 값을 읽음 (역참조)
 *
 * 출력:
 *   ptr  → a의 메모리 주소 (16진수)
 *   *ptr → a의 값 (10)
 */
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int *ptr = &a;

    cout << ptr << " " << *ptr << endl;

    return 0;
}
