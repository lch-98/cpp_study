/*
 * [Topic] Basic Input
 * cin으로 사용자 입력을 받아 변수에 저장하고 출력하는 예제.
 * 공백이 포함된 입력은 getline()을 사용해야 한다는 점에 주의.
 *
 * Key points:
 *   - cin >> var : 공백 전까지 입력 받기
 *   - string 타입으로 문자열, int 타입으로 정수 입력 받기
 */
#include <iostream>
using namespace std;

int main() {
    string name;
    int age;

    cout << "이름을 입력하세요: ";
    cin >> name;

    cout << "나이를 입력하세요: ";
    cin >> age;

    cout << "안녕하세요, " << name << "님! 나이는 " << age << "살이군요." << endl;
}
