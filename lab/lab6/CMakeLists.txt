cmake_minimum_required(VERSION 2.8)
project(lab6)

#set(CMAKE_LIBRARY_PATH /usr/X11/lib /usr/X11/include/X11 ${CMAKE_LIBRARY_PATH})
#find_package(X11)
#if (X11_FOUND)
#    include_directories(${X11_INCLUDE_DIRS})
#    target_link_libraries(lab6 ${X11_LIBRARIES})
#endif (X11_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -L/usr/X11/lib -lX11")

set(SOURCE_FILES Main.cpp easygl.cpp graphics.cpp Shape.cpp ShapeArray.cpp Triangle.cpp Rectangle.cpp Rectangle.h Circle.cpp Circle.h Polygon.cpp Polygon.h)
add_executable(lab6 ${SOURCE_FILES})
