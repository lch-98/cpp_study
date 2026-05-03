/*
 * [Topic] Passing Pointer to Function
 * 포인터를 함수 매개변수로 받아 원본 값을 수정하는 예제.
 *
 * change_negative(int* _val):
 *   - 포인터로 원본에 직접 접근해 양수를 음수로 변환
 *   - 이미 음수인 값은 변경하지 않음
 *
 * 값(value)으로 넘겼다면 원본이 바뀌지 않는다는 점과 비교해볼 것.
 * → value_reference_pointer.cpp 참고
 */
#include <iostream>
using namespace std;

void change_negative(int *_val) {
    if (*_val > 0) {
        *_val = -(*_val);
    }
}

int main() {
    int a = 3, b = -3;
    change_negative(&a);
    change_negative(&b);

    cout << "change_negative(a) : " << a << endl;
    cout << "change_negative(b) : " << b << endl;
    return 0;
}
