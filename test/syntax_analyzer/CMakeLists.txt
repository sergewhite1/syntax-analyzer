cmake_minimum_required(VERSION 3.10)

project(test-syntax-analyzer)

add_executable(${PROJECT_NAME}
  ../same_value.cpp
  ../same_value.h
  test_syntax_analyzer.cpp)

set_default_compiler_options(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} syntax-analyzer-lib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${PROJECT_NAME}
                   COMMENT "Run Unit Tests: ${PROJECT_NAME}"
)