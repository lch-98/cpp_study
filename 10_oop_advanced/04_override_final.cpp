/*
 * [Topic] override & final
 * 실수를 컴파일 타임에 잡아주는 C++11 키워드.
 *
 * override:
 *   - 부모의 virtual 함수를 재정의한다고 명시
 *   - 부모에 해당 시그니처가 없으면 컴파일 에러 → 오타/시그니처 불일치 방지
 *
 * final:
 *   - 클래스: 더 이상 상속 불가
 *   - 함수: 더 이상 override 불가
 *
 * Practice:
 *   - override 없이 함수 이름을 살짝 바꿔서 실수해보고 버그 찾기
 *   - Final 클래스를 상속하려 하면 어떤 에러가 나는지 확인
 */
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() const { cout << "...\n"; }
    virtual void move() const { cout << "이동\n"; }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override { cout << "멍멍!\n"; }
    void move() const override { cout << "뛰어감\n"; }
    // void spek() const override { }  // 컴파일 에러: Animal에 spek 없음
};

// final 클래스 — 더 이상 상속 불가
class GuideDog final : public Dog {
public:
    void speak() const override { cout << "조용한 멍!\n"; }
};

// class SuperGuideDog : public GuideDog { };  // 컴파일 에러

// 특정 함수만 final
class Cat : public Animal {
public:
    void speak() const override final { cout << "야옹!\n"; }
};

// class MutantCat : public Cat {
//     void speak() const override { }  // 컴파일 에러
// };

int main() {
    Dog d;
    d.speak();
    d.move();

    GuideDog g;
    g.speak();

    Animal* a = new GuideDog();
    a->speak();  // 동적 바인딩 → GuideDog::speak
    delete a;

    return 0;
}
