/*
 * [Topic] CMake Project Structure - Header File
 * 클래스 선언부만 담는 헤더 파일.
 *
 * #pragma once : 동일 헤더가 여러 번 include 되어도 한 번만 처리 (include guard)
 * private 멤버는 외부에서 직접 접근 불가 → 캡슐화(encapsulation) 실현
 */
// Robot.h
#pragma once
#include <string>
using namespace std;

class Robot {
private:
    string name;
    double speed;
public:
    Robot(string n, double s);
    void printStatus();
};
