cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME syntax-analyzer-demo)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  schildt_syntax_analyzer/schildt_syntax_analyzer.cpp
  schildt_syntax_analyzer/schildt_syntax_analyzer.h
  syntax_analyzer/syntax_analyzer.cpp
  syntax_analyzer/syntax_analyzer.h
  main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ./)

target_link_libraries(${PROJECT_NAME} schildt)

add_subdirectory(schildt)
