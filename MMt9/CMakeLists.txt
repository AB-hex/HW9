cmake_minimum_required(VERSION 3.17)
project(MMt9)

set(CMAKE_CXX_STANDARD 11)

add_executable(MMt9 main.cpp string.h string.cpp field.cpp field.h port.cpp
        port.h input.h ip.cpp ip.h)