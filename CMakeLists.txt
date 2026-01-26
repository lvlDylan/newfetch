cmake_minimum_required(VERSION 4.1)
project(newfetch C)

set(CMAKE_C_STANDARD 99)

include_directories(headers)

set(HEADERS
        headers/system.h
)

add_executable(
        newfetch
        ${HEADERS}
        main.c
        utils/system.c
)
