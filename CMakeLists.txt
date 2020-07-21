cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME syntax-analyzer-project)

project(${PROJECT_NAME})

add_subdirectory(src)

enable_testing()

add_subdirectory(test)
