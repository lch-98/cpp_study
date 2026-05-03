/*
 * [Topic] Inheritance — 상속
 * 기존 클래스(부모)를 확장해 새 클래스(자식)를 만드는 기본 상속 예제.
 *
 * Key points:
 *   - public 상속  : 부모의 public/protected → 그대로 유지
 *   - protected 멤버: 자식 클래스에서 접근 가능, 외부에서 접근 불가
 *   - 생성자 체인  : 자식 생성 시 부모 생성자가 먼저 호출됨
 *   - 소멸자 체인  : 자식 소멸자 → 부모 소멸자 순서
 *
 * Practice:
 *   - Employee에 department 필드 추가해보기
 *   - Manager 클래스(Employee 상속)를 직접 만들어보기
 */
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Person 생성: " << name << "\n";
    }
    virtual ~Person() {  // 가상 소멸자 (다형성 사용 시 필수)
        cout << "Person 소멸: " << name << "\n";
    }
    void introduce() const {
        cout << "이름: " << name << ", 나이: " << age << "\n";
    }
};

class Employee : public Person {
    string company;
    double salary;
public:
    Employee(string n, int a, string c, double s)
        : Person(n, a), company(c), salary(s) {
        cout << "Employee 생성: " << name << " @ " << company << "\n";
    }
    ~Employee() override {
        cout << "Employee 소멸: " << name << "\n";
    }
    void introduce() const {
        Person::introduce();  // 부모 메서드 명시적 호출
        cout << "회사: " << company << ", 연봉: " << salary << "\n";
    }
};

int main() {
    cout << "=== 스택 객체 ===\n";
    {
        Employee e("홍길동", 30, "Anthropic", 80000);
        e.introduce();
    }

    cout << "\n=== 포인터 (다형성 준비) ===\n";
    Person* p = new Employee("이순신", 45, "Navy", 120000);
    p->introduce();  // Person::introduce 호출 (아직 virtual 아님)
    delete p;

    return 0;
}
