/*
 * [Topic] Struct with Pointer Parameter
 * 구조체 배열을 포인터(배열 decay)로 함수에 전달하는 예제.
 *
 * 왜 포인터/참조로 넘기나?
 *   - 큰 구조체를 값으로 넘기면 전체 복사가 발생해 메모리/시간 낭비
 *   - 배열을 함수 인자로 넘기면 자동으로 포인터로 decay됨
 *
 * Person adult[] 와 Person* adult 는 함수 매개변수에서 동일하게 동작한다.
 */
#include <iostream>
#include <string>
using namespace std;

struct Person
{
    string name;
    int age;
    float height;
    float weight;
};

void check_age(Person _adult[], int _count) {
    for (int i=0; i < _count; i++)
    {
        if (_adult[i].age >= 25)
        {
            cout << "name : " << _adult[i].name << endl;
        }
    }
}

int main () {
    Person adult[3] = {
        {"A", 24, 180, 70},
        {"B", 22, 165, 55},
        {"C", 30, 170, 65}
    };
    check_age(adult, 3);
    return 0;
}
