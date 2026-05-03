# 08. GUI with Qt

Qt 프레임워크를 사용해 첫 번째 데스크탑 GUI 애플리케이션을 만듭니다.

---

## 파일

| 파일 | 설명 |
|------|------|
| [QT기본실행/src/main.cpp](QT기본실행/src/main.cpp) | QPushButton 하나를 띄우는 최소 Qt 예제 |

---

## 빌드 환경 설정

**필수 설치:**
- [Qt 6 (또는 Qt 5)](https://www.qt.io/download) — Open Source 버전 사용 가능
- CMake 3.16+
- C++ 17 이상 컴파일러

**CMakeLists.txt 수정:**
```cmake
# Qt 설치 경로를 본인 환경에 맞게 수정
set(CMAKE_PREFIX_PATH "C:/Qt/6.x.x/msvc2022_64")
```

**빌드:**
```bash
cd QT기본실행
mkdir build && cd build
cmake .. && cmake --build .
```

---

## 핵심 구조

```cpp
QApplication app(argc, argv);  // 이벤트 루프 초기화 (필수, 가장 먼저)

QPushButton button("First Qt!");
button.resize(200, 100);
button.show();

return app.exec();  // 이벤트 루프 시작 (창 닫힐 때까지 블로킹)
```

### Qt 다음 학습 방향
- Signal & Slot : 위젯 간 이벤트 연결
- QWidget 상속 : 커스텀 위젯 제작
- Qt Designer : UI를 GUI 도구로 설계
- QMainWindow : 메뉴바, 툴바, 상태바 포함 메인 창

---

> **앞 단계:** [07_sockets](../07_sockets/)
