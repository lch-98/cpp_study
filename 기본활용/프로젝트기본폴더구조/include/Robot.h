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