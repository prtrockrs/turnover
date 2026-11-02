cmake_minimum_required(VERSION 3.20)

project(TurnoverGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(TurnoverGame
    src/main.cpp
    src/core/Game.cpp
)

target_include_directories(TurnoverGame PRIVATE
    src
)

find_package(raylib REQUIRED)

target_link_libraries(TurnoverGame PRIVATE
    raylib
)