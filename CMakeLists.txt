cmake_minimum_required(VERSION 3.9.6)
project(MAP C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")

add_executable(MAP main.c map_mtm.c map_mtm.h node.h node.c test_utilities.h)