cmake_minimum_required(VERSION 3.14)
project(SocketStudy)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server server/main.cpp)
add_executable(Client client/main.cpp)

# Windows 소켓 라이브러리 추가
target_link_libraries(Server ws2_32)
target_link_libraries(Client ws2_32)