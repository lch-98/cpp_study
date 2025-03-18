#include <iostream>
using namespace std;
/*
// static 변수
void func() {
    int a = 10;
    static int b = 10;

    a++;
    b++;

    cout << a << " " << b << endl;
}

int main() {
    func();
    func();
    func();
    func();
    func();

    return 0;
}
*/

// const 변수
int main() {
    int a = 0;
    int b = 1;
    const int *ptr = &a; // 가르키는 값을 상수화 한거임 따라서 값을 바꾸는건 허용 X
    ptr = &b; // 따라서 주소 변경은 가능

    cout << a << " " << &a << " " << &b << " " << ptr << " " << *ptr << endl;
}