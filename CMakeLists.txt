cmake_minimum_required(VERSION 3.23)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 main.cpp offsets.hpp memory_controller.h memory_controller.cpp include.h main_ch.cpp main_ch.h)