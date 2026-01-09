cmake_minimum_required(VERSION 3.21)
project(allocators)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(allocators main.cpp)
target_compile_options(allocators PRIVATE "-fsanitize=leak")
target_link_libraries(allocators PRIVATE "-fsanitize=leak")
