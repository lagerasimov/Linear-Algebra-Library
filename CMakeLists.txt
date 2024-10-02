cmake_minimum_required(VERSION 3.10)
project(linalg) 
add_executable(proga source/main.cpp)
add_subdirectory(./LinalgLibrary/)
target_link_libraries(proga PUBLIC linalg)

