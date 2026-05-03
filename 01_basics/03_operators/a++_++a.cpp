/*
 * [Topic] Post-increment vs Pre-increment
 * 후위(a++)와 전위(++a) 연산자의 동작 차이를 확인하는 예제.
 *
 *   a++ : 현재 값을 먼저 반환한 뒤 증가 (반환값 = 증가 전)
 *   ++a : 먼저 증가한 뒤 반환 (반환값 = 증가 후)
 *
 * 반복문에서 단독으로 쓸 때는 결과가 동일하지만,
 * 표현식 안에서 쓸 때는 이 차이가 중요하다.
 */
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 1;

    cout << a++ << " " << b++ << endl;
    a = 1, b = 1;
    cout << ++a << " " << ++b << endl;

}
