cmake_minimum_required(VERSION 3.6)
project(lab5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DBentry.cpp DBentry.h TreeNode.cpp TreeNode.h TreeDB.cpp TreeDB.h)
add_executable(lab5 ${SOURCE_FILES})