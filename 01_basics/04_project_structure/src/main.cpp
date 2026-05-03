/*
 * [Topic] CMake Project Structure - Entry Point
 * 헤더/소스 파일을 분리한 실제 프로젝트 구조 예제.
 * Robot 클래스를 인스턴스화해 메서드를 호출한다.
 *
 * 빌드 방법:
 *   mkdir build && cd build
 *   cmake .. && cmake --build .
 */
// main.cpp
#include "Robot.h"

int main() {
    Robot r("M4", 2.5);
    r.printStatus();
}
