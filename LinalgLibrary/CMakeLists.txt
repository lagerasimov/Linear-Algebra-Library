cmake_minimum_required(VERSION 3.10)
project(linalglab) 
add_library(linalg ./source/linalg.cpp)
target_include_directories(linalg PUBLIC ./include)
