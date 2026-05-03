/*
 * [Topic] Pure Virtual & Abstract Class — 순수 가상 함수와 추상 클래스
 * 인터페이스를 정의하는 추상 클래스 패턴.
 *
 * 순수 가상 함수: virtual void func() = 0;
 *   - 구현 없음, 자식에서 반드시 구현해야 함
 *   - 하나라도 있으면 그 클래스는 추상 클래스
 *   - 추상 클래스는 직접 인스턴스화 불가
 *
 * 인터페이스 패턴:
 *   - 멤버 변수 없음, 순수 가상 함수만으로 구성
 *   - 다른 언어의 interface와 동일한 역할
 *
 * Practice:
 *   - ILogger 인터페이스를 직접 설계하고 FileLogger, ConsoleLogger 구현
 */
#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 인터페이스 (순수 추상 클래스)
class ISerializer {
public:
    virtual string serialize(const string& data) const = 0;
    virtual string deserialize(const string& raw) const = 0;
    virtual ~ISerializer() = default;
};

class JsonSerializer : public ISerializer {
public:
    string serialize(const string& data) const override {
        return "{\"value\": \"" + data + "\"}";
    }
    string deserialize(const string& raw) const override {
        // 단순화된 파싱
        auto start = raw.find('"', raw.find(':') + 1) + 1;
        auto end = raw.rfind('"');
        return raw.substr(start, end - start);
    }
};

class XmlSerializer : public ISerializer {
public:
    string serialize(const string& data) const override {
        return "<value>" + data + "</value>";
    }
    string deserialize(const string& raw) const override {
        auto start = raw.find('>') + 1;
        auto end = raw.rfind('<');
        return raw.substr(start, end - start);
    }
};

void process(const ISerializer& ser, const string& data) {
    auto raw = ser.serialize(data);
    cout << "직렬화: " << raw << "\n";
    cout << "역직렬화: " << ser.deserialize(raw) << "\n\n";
}

int main() {
    JsonSerializer json;
    XmlSerializer xml;

    process(json, "hello world");
    process(xml, "hello world");

    // 추상 클래스는 직접 생성 불가
    // ISerializer s;  // 컴파일 에러

    return 0;
}
