cmake_minimum_required(VERSION 3.21)
project(DataStructure C)

set(CMAKE_C_STANDARD 11)

add_executable(DataStructure main.c)
add_executable(
        SqList
        0201_SqList/SqList-main.c
        Status/Status.c
        Status/Status.h
        0201_SqList/SqList.c
        0201_SqList/SqList.h
)
