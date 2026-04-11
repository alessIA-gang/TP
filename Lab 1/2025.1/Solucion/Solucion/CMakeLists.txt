cmake_minimum_required(VERSION 3.31)
project(proyecto)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyecto main.cpp
        biblioteca/funcionesAdicionales.cpp
        biblioteca/funcionesAdicionales.h)
