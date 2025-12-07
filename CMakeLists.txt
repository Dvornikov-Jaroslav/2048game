cmake_minimum_required(VERSION 3.16)
project(game2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Test)

add_library(game2048_lib
    src/game2048.cpp
    src/game2048.hpp
)
target_include_directories(game2048_lib PUBLIC src)
target_link_libraries(game2048_lib Qt6::Core)

add_executable(2048
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.hpp
)
target_link_libraries(2048 Qt6::Widgets game2048_lib)

add_subdirectory(tests)
