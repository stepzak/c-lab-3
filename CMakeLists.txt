cmake_minimum_required(VERSION 3.30)
project(c_lab_4 C)

set(CMAKE_C_STANDARD 23)

add_executable(c_lab_4 main.c
        check_space.c
        read.c
        caesar.c)
