cmake_minimum_required(VERSION 3.21)
project(DataStructure C)

set(CMAKE_C_STANDARD 11)

add_executable(DataStructure main.c)
add_executable(
        SqList
        0201_SqList/SqList-main.c
        0201_SqList/SqList.c
        0201_SqList/SqList.h
        Status/Status.c
        Status/Status.h
)
add_executable(
        LinkList
        0202_LinkList/LinkList-main.c
        0202_LinkList/LinkList.c
        0202_LinkList/LinkList.h
        Status/Status.c
        Status/Status.h
)
