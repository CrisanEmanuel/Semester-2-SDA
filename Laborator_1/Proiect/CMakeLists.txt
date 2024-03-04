cmake_minimum_required(VERSION 3.25)
project(Proiect)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proiect
        Coada.cpp
        Coada.h
        main.cpp
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
