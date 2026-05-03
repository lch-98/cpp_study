cmake_minimum_required(VERSION 3.10)
project(WeatherApp)

# Set the path to the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "/source-charset:utf-8")

add_executable(WeatherApp main.cpp)

target_link_libraries(WeatherApp PRIVATE CURL::libcurl jsoncpp_lib)