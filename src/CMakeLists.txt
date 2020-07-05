cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME syntax-analyzer-demo)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} schildt)

add_subdirectory(schildt)
