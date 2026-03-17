cmake_minimum_required(VERSION 3.21)
project(vector)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(vector main.cpp)
target_compile_options(vector PUBLIC -Wall -Wextra -Werror -fsanitize=undefined,address)
target_link_options(vector PUBLIC -fsanitize=undefined,address)
