/*
 * [Topic] Factory Pattern — 팩토리
 * 객체 생성 로직을 호출자에서 분리한다.
 *
 * 팩토리 메서드: 서브클래스가 생성할 클래스를 결정
 * 추상 팩토리: 관련된 객체 군(family)을 생성
 *
 * 사용 예: UI 테마, DB 드라이버, 로그 핸들러
 *
 * Practice:
 *   - LoggerFactory 추가: "file" → FileLogger, "console" → ConsoleLogger
 *   - 팩토리에 등록(register) 기능 추가 (플러그인 패턴)
 */
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
using namespace std;

// 추상 인터페이스
class Shape {
public:
    virtual double area() const = 0;
    virtual string name() const = 0;
    virtual ~Shape() = default;
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

// 팩토리 — 문자열로 객체 생성 (등록 기반)
class ShapeFactory {
    using Creator = function<unique_ptr<Shape>()>;
    unordered_map<string, Creator> registry;

    ShapeFactory() {
        // 기본 도형 등록
        registry["circle_5"]    = []{ return make_unique<Circle>(5.0); };
        registry["rect_4x6"]    = []{ return make_unique<Rectangle>(4, 6); };
    }
public:
    static ShapeFactory& instance() {
        static ShapeFactory f;
        return f;
    }

    void registerShape(const string& key, Creator creator) {
        registry[key] = move(creator);
    }

    unique_ptr<Shape> create(const string& key) {
        auto it = registry.find(key);
        if (it == registry.end())
            throw runtime_error("알 수 없는 도형: " + key);
        return it->second();
    }
};

int main() {
    auto& factory = ShapeFactory::instance();

    // 기본 도형 생성
    auto s1 = factory.create("circle_5");
    auto s2 = factory.create("rect_4x6");
    cout << s1->name() << " 넓이: " << s1->area() << "\n";
    cout << s2->name() << " 넓이: " << s2->area() << "\n";

    // 새 도형 동적 등록
    factory.registerShape("big_circle", []{ return make_unique<Circle>(100.0); });
    auto s3 = factory.create("big_circle");
    cout << s3->name() << " 넓이: " << s3->area() << "\n";

    return 0;
}
