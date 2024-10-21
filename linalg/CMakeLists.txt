set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(linalg ./source/linalg.cpp)
target_include_directories(linalg PUBLIC ./include)
