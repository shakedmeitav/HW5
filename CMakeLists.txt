cmake_minimum_required(VERSION 3.9.6)
project(Hw3_mtmflix C)

set(CMAKE_C_STANDARD 99)
add_executable(Hw3_mtmflix main.c mtmflix.c user.h user.c series.h series.c mtm_ex3.h mtmflix.h list.h set.h)
target_link_libraries(Hw3_mtmflix ${CMAKE_SOURCE_DIR}/libmtm.a ${CMAKE_SOURCE_DIR}/libmtm_ex3.a)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")