#include <iostream>
using namespace std;

struct test
{
    int a;
    int b;
};


int main() {
    test tc;
    tc.a = 1;
    tc.b = 2;
    
    test tc2;
    tc2.a = 3;
    tc2.b = 4;
    
    cout << tc.a << " " << tc.b << endl;
    cout << tc2.a << " " << tc2.b << endl;

    return 0;
}