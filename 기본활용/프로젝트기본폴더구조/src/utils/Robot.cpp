// Robot.cpp
#include "Robot.h"
#include <iostream>
using namespace std;

Robot::Robot(string n, double s) : name(n), speed(s) {}
void Robot::printStatus() {
    cout << name << "의 속도: " << speed << endl;
}