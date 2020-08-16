cmake_minimum_required(VERSION 3.10)

include (set_default_compiler_options.cmake)

set(PROJECT_NAME syntax-analyzer-project)

project(${PROJECT_NAME})

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(src)

enable_testing()

add_subdirectory(test)
