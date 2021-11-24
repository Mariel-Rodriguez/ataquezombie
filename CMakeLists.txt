cmake_minimum_required(VERSION 3.20)
project(informatica2)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
add_executable(informatica2 main.cpp Juego.cpp Juego.h)
target_link_libraries(informatica2 sfml-system sfml-window sfml-graphics sfml-audio)