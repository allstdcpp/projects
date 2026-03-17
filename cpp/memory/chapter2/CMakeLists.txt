cmake_minimum_required(VERSION 3.21)
project(chapter2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(chapter2 main.cpp)
target_link_libraries(chapter2 PUBLIC -fsanitize=address -fsanitize=undefined)
target_compile_options(chapter2 PUBLIC -fsanitize=address -fsanitize=undefined)
