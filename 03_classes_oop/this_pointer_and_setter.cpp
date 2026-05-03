/*
 * [Topic] this Pointer & Setter
 * this 포인터와 setter 메서드를 이용한 멤버 변수 초기화 예제.
 *
 * this 포인터:
 *   - 모든 멤버 함수 안에서 자동으로 사용 가능
 *   - 현재 객체 자신을 가리키는 포인터
 *   - 매개변수 이름과 멤버 변수 이름이 같을 때 구분하기 위해 사용
 *     예) this->job = job;  (왼쪽 = 멤버변수, 오른쪽 = 매개변수)
 *
 * setter:
 *   - private 멤버를 외부에서 안전하게 수정하는 공개 메서드
 *   - 직접 대입 초기화 대신 setter를 쓰면 유효성 검사 로직을 추가하기 쉬움
 */
#include <iostream>
#include <string>
using namespace std;

struct infoStruct {
	string job;
	int age;

	void hello() {
		cout << "안녕하세요 " << this->job << "입니다." << "\n";
	}
};

class infoClass {
public:
	string job;
	int age;
	void hello() { cout << "안녕하세요 HMI engineer입니다." << "\n"; }

	void setInfo(string job, int age) {
		// 매개변수와 멤버 변수 이름이 같을 경우 구분을 위해 'this->' 를사용
		this->job = job;
		this->age = age;
	}
};

int main() {
	cout << "*** 여기서부터 Struct에 대한 설명 ***\n";
	infoStruct person1 = { "engineer_PLC", 29 };
	infoStruct* ptr_person1 = &person1;

	cout << "name: " << ptr_person1->job << "\n";
	cout << "name: " << (*ptr_person1).job << "\n";
	cout << "age: " << ptr_person1->age <<  "\n";
	cout << "age: " << (*ptr_person1).age << "\n";
	ptr_person1->hello();
	(*ptr_person1).hello();

	cout << "\n *** 여기서부터 Class에 대한 설명 ***\n";
	infoClass person2;
	person2.setInfo("engineer_HMI", 30);
	infoClass* ptr_person2 = &person2;

	cout << "name: " << ptr_person2->job << "\n";
	cout << "name: " << (*ptr_person2).job << "\n";
	cout << "age: " << ptr_person2->age << "\n";
	cout << "age: " << (*ptr_person2).age << "\n";
	ptr_person2->hello();
	(*ptr_person2).hello();

}
