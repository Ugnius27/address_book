cmake_minimum_required(VERSION 3.28)
project(task2 C)

set(CMAKE_C_STANDARD 11)

add_executable(task2 main.c
        console.c
        interpreter.c
        linked_list.c
        linked_list_utils.c)
