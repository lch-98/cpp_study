#include <iostream>
#include <vector>
using namespace std;
int main() {
    int arr[] = {1, 2, 3};
    int *ptr = arr;
    
    cout << ptr << " " << ptr+1  << endl;
    cout << *(ptr+0)  << " " <<*(ptr+1) << endl;
    cout << &arr[0] << " " << &arr[1] << endl;
    cout << arr[0] << " " << arr[1] << endl;

    return 0;    
}