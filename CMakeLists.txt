cmake_minimum_required(VERSION 3.21)
project(dll_inject C)

set(CMAKE_C_STANDARD 99)

add_executable(dll_inject main.c dll_inject.c dll_inject.h)
