cmake_minimum_required(VERSION 3.21)
project(trie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(trie main.cpp)
target_compile_options(trie PUBLIC -Wall -Wextra -Werror -fsanitize=undefined,address)
target_link_options(trie PUBLIC -fsanitize=undefined,address)
