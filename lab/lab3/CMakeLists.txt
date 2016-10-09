cmake_minimum_required(VERSION 3.6)
project(lab3_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Rparser.cpp Rparser.h Node.cpp Node.h Resistor.cpp Resistor.h)
add_executable(lab3_1 ${SOURCE_FILES})