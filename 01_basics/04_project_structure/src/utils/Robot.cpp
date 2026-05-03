/*
 * [Topic] CMake Project Structure - Implementation
 * Robot 클래스의 메서드 구현부.
 * 헤더(Robot.h)와 구현(.cpp)을 분리함으로써 컴파일 단위를 나누고
 * 인터페이스와 구현을 독립적으로 관리할 수 있다.
 *
 * 이니셜라이저 리스트(: name(n), speed(s))를 사용해
 * 멤버 변수를 생성자 본문 실행 전에 초기화한다.
 */
// Robot.cpp
#include "Robot.h"
#include <iostream>
using namespace std;

Robot::Robot(string n, double s) : name(n), speed(s) {}
void Robot::printStatus() {
    cout << name << "의 속도: " << speed << endl;
}
