cmake_minimum_required(VERSION 2.8)

project(hw2)
add_executable(hw2 main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(hw2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )