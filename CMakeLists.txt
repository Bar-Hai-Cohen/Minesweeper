cmake_minimum_required(VERSION 3.23)
project(Minesweeper C)

set(CMAKE_C_STANDARD 99)

add_executable(Minesweeper main.c Minesweeper.c colorPrint.c )
