/*
 * [Topic] const vs volatile
 *
 * const:
 *   - 컴파일러가 값 변경을 허용하지 않음
 *   - 주로 매직 넘버를 상수로 정의할 때 사용
 *
 * volatile:
 *   - 컴파일러 최적화를 억제 → 매번 메모리에서 직접 읽음
 *   - 하드웨어 레지스터, 인터럽트 핸들러, 멀티스레드 공유 변수 등에 사용
 *   - 단독으로는 스레드 안전을 보장하지 않음 (mutex 필요)
 */
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
