#include <iostream>

using namespace std;

const int CONST_VAR = 10;  // 컴파일러가 이 값을 변경 불가능한 상수로 인식
volatile int VOLATILE_VAR = 10; // 외부 요인에 의해 변경될 수 있는 변수

int main() {
    int x = CONST_VAR;
    cout << "CONST_VAR: " << x << endl;

    // CONST_VAR = 20; // 값을 바꾸려고 하면 에러가 발생함

    int y = VOLATILE_VAR;
    cout << "수정 전 VOLATILE_VAR: " << y << endl;

    VOLATILE_VAR = 20;  // 정상적으로 변경 가능
    y = VOLATILE_VAR;
    cout << "수정 후 VOLATILE_VAR: " << y << endl;

    return 0;
}
