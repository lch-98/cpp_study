// 구조체는 기본 접근이 public 클래스는 기본 접근이 private
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