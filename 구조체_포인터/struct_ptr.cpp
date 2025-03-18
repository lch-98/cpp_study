//구조체를 포인터 구조체 매개변수로 받는 이유 -> 메모리 관리를 위해 (너무 큰 구조체 그냥 복사시 메모리를 잡아먹기 때문에)
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