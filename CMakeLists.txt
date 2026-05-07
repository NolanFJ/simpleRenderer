cmake_minimum_required(VERSION 3.10)

project(simpleRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (HEADERS
    src/tgaimage.hpp
)

set (SOURCES
    src/main.cpp
    src/tgaimage.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})