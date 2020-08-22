cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME test-syntax-analyzer)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  ../same_value.cpp
  ../same_value.h
  test_syntax_analyzer.cpp)

set_default_compiler_options(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} syntax-analyzer-lib)

function (add_syntax_analyzer_test class testCase)
  add_test(test_${class}_${testCase} ${PROJECT_NAME} --class ${class} --testCase ${testCase})
endfunction()

function(add_simplest_ananlyzer_test_cases)
  add_syntax_analyzer_test(SimplestSyntaxAnalyzer Add)
  add_syntax_analyzer_test(SimplestSyntaxAnalyzer EmptyExpression)
endfunction()

# Call add_*_test_cases functions

add_simplest_ananlyzer_test_cases()
