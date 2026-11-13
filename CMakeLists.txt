cmake_minimum_required(VERSION 3.20)
project(Sandfall VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

add_executable(game
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)