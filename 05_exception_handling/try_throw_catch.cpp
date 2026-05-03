/*
 * [Topic] Exception Handling: try / throw / catch
 * C++ 예외 처리의 기본 흐름을 보여주는 예제.
 *
 * 동작:
 *   1. try 블록 안에서 throw로 예외 발생
 *   2. throw 이후 코드는 실행되지 않음 (즉시 catch로 이동)
 *   3. throw 타입과 일치하는 catch 블록이 처리
 *   4. catch(...) : 모든 타입을 잡는 catch-all
 *
 * 이 예제에서 던지는 타입:
 *   - int   : catch(int a) 가 처리
 *   - float : catch(...) 가 처리 (float 전용 catch 없음)
 *   - char  : catch(...) 가 처리
 */
#include <iostream>
using namespace std;

int main() {
    try
    {
        int input;
        cout << "choose integrity: ";
        cin >> input;
        if (input > 0) {
            cout << "throw 1" << endl;
            throw 1;
            cout << "after throw 1" << endl;
        }
        if (input < 0) {
            cout << "throw -1.0f" << endl;
            throw -1.0f;
            cout << "after throw -1.0f" << endl;
        }
        if (input == 0) {
            cout << "throw Z" << endl;
            throw 'Z';
            cout << "after throw Z" << endl;
        }
    }
    catch(int a)
    {
        cout << "catch " << a << endl;
    }
    catch(...)
    {
        cout << "all catch" << endl;
    }
    return 0;
}
