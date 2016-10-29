cmake_minimum_required(VERSION 3.6)
project(lab4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/Desktop/ClassNotes/ECE244/lab/lab4")

set(SOURCE_FILES main.cpp Resistor.cpp Resistor.h Node.cpp Node.h Rparser.h Rparser.cpp ResistorList.cpp ResistorList.h NodeList.cpp NodeList.h)
add_executable(lab4 ${SOURCE_FILES})