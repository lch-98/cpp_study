#include <iostream>
using namespace std;

void addByValue(int x) { // 복사본만 증가
    x++;
    cout << "x= " << x << ", ";
}
void addByRef(int &x) { // 원본 증가
    x++; 
    cout << "x= " << x << ", ";
}        
void addByPtr(int *x) { // 포인터가 가리키는 값 증가
    (*x)++;
    cout << "x= " << *x << ", ";
}

int main() {
    int a = 10;
    addByValue(a);   // a = 10
    cout << "a= " << a << "\n";

    addByRef(a);     // a = 11
    cout << "a= " << a << "\n";

    addByPtr(&a);    // a = 12
    cout << "a= " << a << "\n";
    return 0;
}