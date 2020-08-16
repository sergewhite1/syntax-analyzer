cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME syntax-analyzer-demo)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ./)

set_default_compiler_options(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} schildt syntax-analyzer-lib)

add_subdirectory(schildt)
add_subdirectory(syntax_analyzer)
