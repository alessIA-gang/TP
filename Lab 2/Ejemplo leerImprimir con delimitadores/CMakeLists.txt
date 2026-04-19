cmake_minimum_required(VERSION 4.0)
project(XDD)

set(CMAKE_CXX_STANDARD 20)

add_executable(XDD main.cpp
        BIBLIOTECAS/funciones.cpp
        BIBLIOTECAS/funciones.h)
