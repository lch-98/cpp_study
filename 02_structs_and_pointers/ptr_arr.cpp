/*
 * [Topic] Pointer Arithmetic & Array
 * 배열과 포인터의 관계, 포인터 산술 연산을 확인하는 예제.
 *
 * 핵심:
 *   - 배열 이름(arr)은 첫 번째 원소의 주소(&arr[0])와 동일
 *   - ptr[i] 와 *(ptr + i) 는 완전히 동일한 표현
 *   - &ptr  : 포인터 변수 자체의 주소 (ptr이 저장된 위치)
 *   - ptr   : 포인터가 가리키는 주소 (== arr의 주소)
 *   - *ptr  : 해당 주소의 값
 */
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
