/*
 * [Topic] Struct vs Class + Arrow Operator (->)
 * struct와 class의 핵심 차이, 그리고 포인터로 멤버에 접근하는 방법.
 *
 * struct vs class:
 *   - struct : 멤버 기본 접근 제어가 public
 *   - class  : 멤버 기본 접근 제어가 private
 *   - 기능적으로는 동일하며, 관례상 데이터 묶음은 struct, 로직 포함은 class 사용
 *
 * 포인터로 멤버 접근:
 *   ptr->member   ==   (*ptr).member   (완전히 동일)
 */
#include <iostream>
#include <string>
using namespace std;

struct infoStruct {
	string job;
	int age;
	void hello() { cout << "안녕하세요 PLC engineer입니다." << "\n"; }
};

class infoClass {
public:
	string job;
	int age;
	void hello() { cout << "안녕하세요 HMI engineer입니다." << "\n"; }
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
	infoClass person2 = { "engineer_HMI", 30 };
	infoClass* ptr_person2 = &person2;

	cout << "name: " << ptr_person2->job << "\n";
	cout << "name: " << (*ptr_person2).job << "\n";
	cout << "age: " << ptr_person2->age << "\n";
	cout << "age: " << (*ptr_person2).age << "\n";
	ptr_person2->hello();
	(*ptr_person2).hello();

}
