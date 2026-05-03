/*
 * [Topic] Template Specialization — 템플릿 특수화
 * 특정 타입에 대해 다른 구현을 제공한다.
 *
 * 전체 특수화: template<> class Foo<int> { ... }
 * 부분 특수화: template<typename T> class Foo<T*> { ... }  (함수는 불가)
 *
 * Practice:
 *   - TypeName<double>을 추가해보기
 *   - Converter<bool>을 특수화해서 "true"/"false" 문자열로 변환
 */
#include <iostream>
#include <string>
using namespace std;

// 기본 템플릿: 타입 이름 출력
template<typename T>
struct TypeName {
    static string get() { return "unknown"; }
};

// 전체 특수화
template<> struct TypeName<int>    { static string get() { return "int"; } };
template<> struct TypeName<float>  { static string get() { return "float"; } };
template<> struct TypeName<string> { static string get() { return "string"; } };

// 포인터에 대한 부분 특수화
template<typename T>
struct TypeName<T*> {
    static string get() { return TypeName<T>::get() + "*"; }
};

// 기본 Converter 템플릿
template<typename T>
struct Converter {
    static string to_string(T val) { return std::to_string(val); }
};

// string 특수화 (to_string이 string에 없으므로)
template<>
struct Converter<string> {
    static string to_string(string val) { return val; }
};

// const char* 특수화
template<>
struct Converter<const char*> {
    static string to_string(const char* val) { return string(val); }
};

int main() {
    cout << TypeName<int>::get() << "\n";
    cout << TypeName<float>::get() << "\n";
    cout << TypeName<string>::get() << "\n";
    cout << TypeName<int*>::get() << "\n";
    cout << TypeName<float*>::get() << "\n";
    cout << TypeName<bool>::get() << "\n";  // unknown

    cout << Converter<int>::to_string(42) << "\n";
    cout << Converter<double>::to_string(3.14) << "\n";
    cout << Converter<string>::to_string("hello") << "\n";
    cout << Converter<const char*>::to_string("world") << "\n";

    return 0;
}
