cmake_minimum_required(VERSION 2.8)
project(graph)
set (CMAKE_CXX_STANDARD 11)

#Bring the headers, such as Student.h into the project
include_directories(includes)

#Can manually add the sources using the set command as follows:
set(SOURCES ./*.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./*.cpp")

add_executable(graph ${SOURCES})

target_link_libraries( graph )

