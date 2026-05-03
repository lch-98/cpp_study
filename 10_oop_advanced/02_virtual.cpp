/*
 * [Topic] Virtual Function — 가상 함수와 동적 바인딩
 * virtual 키워드로 런타임에 실제 타입의 메서드를 호출한다.
 *
 * 정적 바인딩 (non-virtual):
 *   컴파일 타임에 포인터 타입 기준으로 함수 결정
 *
 * 동적 바인딩 (virtual):
 *   런타임에 실제 객체 타입 기준으로 함수 결정 (vtable 사용)
 *
 * Key points:
 *   - 부모 포인터로 자식 메서드를 호출하려면 virtual 필요
 *   - 소멸자도 virtual 선언 필수 (아니면 자식 소멸자 미호출 → 누수)
 *   - override 키워드로 실수 방지
 *
 * Practice:
 *   - virtual을 제거하면 어떤 함수가 호출되는지 확인
 *   - virtual ~Shape()를 일반 소멸자로 바꾸면 누수 발생 확인
 */
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;  // 순수 가상
    virtual string name() const = 0;
    virtual ~Shape() = default;

    void print() const {  // 비가상: 공통 출력 형식 강제
        cout << name() << " 넓이: " << area() << "\n";
    }
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return 3.14159 * r * r; }
    string name() const override { return "Circle(r=" + to_string(r) + ")"; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
    string name() const override { return "Rect(" + to_string(w) + "x" + to_string(h) + ")"; }
};

class Triangle : public Shape {
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const override { return 0.5 * base * height; }
    string name() const override { return "Triangle"; }
};

int main() {
    // 다형성: 부모 포인터 컨테이너에 다양한 자식 객체
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5.0));
    shapes.push_back(make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(make_unique<Triangle>(3.0, 8.0));
    shapes.push_back(make_unique<Circle>(2.5));

    double total = 0;
    for (const auto& s : shapes) {
        s->print();
        total += s->area();
    }
    cout << "총 넓이: " << total << "\n";

    return 0;
}
