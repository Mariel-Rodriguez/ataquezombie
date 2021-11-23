cmake_minimum_required(VERSION 3.20)
project(informatica2)

set(CMAKE_CXX_STANDARD 14)

add_executable(informatica2 main.cpp juegox.cpp juegox.h enemigo.cpp enemigo.h)
find_package(SFML 2.5 COMPONENTS system window graphics)
target_link_libraries(informatica2 sfml-system sfml-window sfml-graphics)