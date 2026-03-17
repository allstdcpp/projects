cmake_minimum_required(VERSION 3.21)
project(hex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(hex main.cpp)
target_compile_options(hex PUBLIC -Wall -Wextra -Werror -fsanitize=undefined,address)
target_link_options(hex PUBLIC -fsanitize=undefined,address)
