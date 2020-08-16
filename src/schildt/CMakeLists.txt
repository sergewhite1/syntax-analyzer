cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME schildt)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
  parser.cpp
  parser.h
)

set_default_compiler_options(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ../)
