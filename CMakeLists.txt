cmake_minimum_required(VERSION 3.9.6)
project(Hw3-mtmflix C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")

add_executable(Hw3-mtmflix main.c list.h set.h mtmflix.h mtm_ex3.h mtmflix.c user.h series.h user.c series.c)