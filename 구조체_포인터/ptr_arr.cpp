#include <iostream>
#include <vector>
using namespace std;
int main() {
    int arr[] = { 1, 2, 3 };
    int* ptr = arr;

    cout << &ptr << endl; // 포인터의 주소
    cout << ptr << " " << ptr + 1 << endl; // 포인터 가르키는 주소 == 배열 주소
    cout << *(ptr + 0) << " " << *(ptr + 1) << endl; // 값
    cout << ptr[0] << " " << ptr[1] << endl; // 값

    cout << arr << " " << arr + 1 << endl; // 배열 주소
    cout << &arr[0] << " " << &arr[1] << endl; // 배열 주소
    cout << arr[0] << " " << arr[1] << endl; // 값
    cout << *(&arr[0]) << " " << *(&arr[1]) << endl; // 값
    return 0;
}