cmake_minimum_required(VERSION 3.21)
project(imp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(imp main.cpp)
target_compile_options(imp PUBLIC -Wall -Wextra -Werror -fsanitize=undefined,address)
target_link_options(imp PUBLIC -fsanitize=undefined,address)
