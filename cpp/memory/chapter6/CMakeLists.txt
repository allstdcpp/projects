cmake_minimum_required(VERSION 3.21)
project(chapter6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(chapter6 main.cpp)
target_link_libraries(chapter6 PUBLIC -fsanitize=address -fsanitize=undefined)
target_compile_options(chapter6 PUBLIC
    -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined)
