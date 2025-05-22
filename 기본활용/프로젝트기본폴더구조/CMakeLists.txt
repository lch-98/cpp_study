cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

# include/ 디렉토리를 인클루드 경로로 추가
include_directories(include)

# src/ 아래 모든 .cpp 파일을 재귀적으로 포함
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(MyProject ${SOURCES})