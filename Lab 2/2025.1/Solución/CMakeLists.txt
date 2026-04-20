cmake_minimum_required(VERSION 4.0)
project(solu)

set(CMAKE_CXX_STANDARD 20)

add_executable(solu main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h)
