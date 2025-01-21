cmake_minimum_required(VERSION 3.20)
project(Vector)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector.cpp
)

add_library(Vector STATIC ${SOURCES})

target_include_directories(Vector PUBLIC libVector)
