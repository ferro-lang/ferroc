cmake_minimum_required(VERSION 3.29)
project(ferroc C)

set(CMAKE_C_STANDARD 23)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(ferroc
        src/main.c
        src/lexer.c
        include/lexer.h
        include/parser.h
        src/parser.c)
