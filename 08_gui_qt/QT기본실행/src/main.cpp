/*
 * [Topic] Basic Qt GUI Application
 * Qt 프레임워크로 첫 번째 GUI 창을 띄우는 최소한의 예제.
 *
 * 핵심 구성:
 *   QApplication : Qt 이벤트 루프 관리자 (반드시 가장 먼저 생성)
 *   QPushButton  : 버튼 위젯 (텍스트, 크기, 표시)
 *   app.exec()   : 이벤트 루프 시작 (창이 닫힐 때까지 블로킹)
 *
 * 빌드 방법:
 *   Qt 설치 후 CMakeLists.txt 의 CMAKE_PREFIX_PATH 를 Qt 설치 경로로 수정
 *   mkdir build && cd build
 *   cmake .. && cmake --build .
 */
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("First Qt!");
    button.resize(200, 100);
    button.show();

    return app.exec();
}
