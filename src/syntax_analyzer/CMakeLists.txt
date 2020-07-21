cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME syntax-analyzer-lib)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
  schildt/schildt_syntax_analyzer.cpp
  schildt/schildt_syntax_analyzer.h
  simplest_syntax_analyzer.cpp
  simplest_syntax_analyzer.h
  syntax_analyzer.cpp
  syntax_analyzer.h
)

target_link_libraries(${PROJECT_NAME} schildt)

target_include_directories(${PROJECT_NAME} PUBLIC ../)
