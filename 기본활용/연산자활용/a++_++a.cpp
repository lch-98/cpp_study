// 후위 연산잔, 전위 연산자 차이
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 1;

    cout << a++ << " " << b++ << endl;
    a = 1, b = 1;
    cout << ++a << " " << ++b << endl;

}