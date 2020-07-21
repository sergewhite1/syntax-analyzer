cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME test-syntax-analyzer)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} test_syntax_analyzer.cpp)
target_link_libraries(${PROJECT_NAME} syntax-analyzer-lib)

function(add_simplest_ananlyzer_test_cases)

add_test(test_simplest_analyzer_Add ${PROJECT_NAME} --class SimplestSyntaxAnalyzer --testCase Add)

endfunction()

# Call add_*_test_cases functions

add_simplest_ananlyzer_test_cases()
