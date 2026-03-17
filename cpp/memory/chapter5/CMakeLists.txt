cmake_minimum_required(VERSION 3.21)
project(chapter3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(chapter3 main.cpp)
target_link_libraries(chapter3 PUBLIC -fsanitize=address -fsanitize=undefined)
target_compile_options(chapter3 PUBLIC
    -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined)
