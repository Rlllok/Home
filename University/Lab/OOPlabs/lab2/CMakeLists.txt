cmake_minimum_required(VERSION 3.0)

project(lab2)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} scanner_db.c ${SOURCES})

set(CMAKE_C_FLAGS "-std=c11 -g")
