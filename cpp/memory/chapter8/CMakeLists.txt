cmake_minimum_required(VERSION 3.21)
project(chapter8)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(chapter8 main.cpp)
target_link_libraries(chapter8 PUBLIC -fsanitize=address -fsanitize=undefined)
target_compile_options(chapter8 PUBLIC
    -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined)
