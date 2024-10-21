cmake_minimum_required(VERSION 3.10)
project(project_linalg) 
add_subdirectory(linalg)
include_directories(test)
add_executable(proga test/main.cpp test/test.cpp)
target_link_libraries(proga PUBLIC linalg)

