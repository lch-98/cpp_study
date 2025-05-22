cmake_minimum_required(VERSION 3.14)
project(MyQtApp)

set(CMAKE_CXX_STANDARD 17)

# vcpkg toolchain 경로 지정 (필요 시)
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MyQtApp src/main.cpp)

target_link_libraries(MyQtApp PRIVATE Qt5::Widgets)