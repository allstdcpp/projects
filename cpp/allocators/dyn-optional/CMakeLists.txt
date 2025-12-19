cmake_minimum_required(VERSION 3.21)
project(dyn)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(dyn main.cpp)
 target_compile_options(dyn PRIVATE "-fsanitize=undefined" )
target_link_libraries(dyn PRIVATE "-fsanitize=undefined")
