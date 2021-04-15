#include <cstring>
#include <memory>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

#include "../../src/syntax_analyzer/schildt/schildt_syntax_analyzer.h"
#include "../../src/syntax_analyzer/simplest_syntax_analyzer.h"

#include "../same_value.h"

#define UNUSED(x) (void)(x)

class TestCase {
public:
  TestCase(const char* expression,
           double expected_result,
           const char* expected_error_msg,
           std::set<std::string>&& available_syntax_analyzers):

           expression_(expression),
           expected_result_(expected_result),
           expected_error_msg_(expected_error_msg),
           available_syntax_analyzers_(available_syntax_analyzers) {}

  const std::string& expression() const { return expression_; }
  double expected_result() const { return expected_result_; }
  const std::string& expected_error_msg() const { return expected_error_msg_; }

  bool available(const std::string& syntax_analyzer_name) const {
    return available_syntax_analyzers_.find(syntax_analyzer_name) !=
           available_syntax_analyzers_.cend();
  }

private:
  std::string expression_;
  double expected_result_;
  std::string expected_error_msg_;
  std::set<std::string> available_syntax_analyzers_;
};

class TestCaseResult {
public:
  TestCaseResult() = default;
  TestCaseResult(const TestCase* test_case_ptr,
                 double actual_result,
                 std::string actual_result_msg):

                 skipped_(false),
                 test_case_ptr_(test_case_ptr),
                 actual_result_(actual_result),
                 actual_result_msg_(actual_result_msg) {}

  bool skipped() const { return skipped_; }

  bool success() const {
    return !skipped_ &&
            same_value(actual_result(), expected_result()) &&
            actual_result_msg() == expected_error_msg();
  }

  std::string expression() const {
    std::string ret;
    if (test_case_ptr_) {
      ret = test_case_ptr_->expression();
    }
    return ret;
  }

  double actual_result() const { return actual_result_;  }

  std::string actual_result_msg() const { return actual_result_msg_; }

  double expected_result() const {
    double ret = 0.0;
    if (test_case_ptr_) {
      ret =  test_case_ptr_->expected_result();
    }
    return ret;
  }

  std::string expected_error_msg() const {
    std::string ret;
    if (test_case_ptr_) {
      ret = test_case_ptr_->expected_error_msg();
    }
    return ret;
  }

private:
  bool skipped_ = true;
  const TestCase* test_case_ptr_ = nullptr;
  double actual_result_ = 0.0;
  std::string actual_result_msg_;
};

TestCaseResult RunTestCase(SyntaxAnalyzer* sa_ptr,
                           const TestCase* test_case_ptr) {
  double actual_result = 0.0;
  std::string actual_result_msg;
  try {
    sa_ptr->setExpression(test_case_ptr->expression());
    actual_result = sa_ptr->getValue();
  } catch (const SyntaxAnalyzerException& e) {
     actual_result_msg = e.what();
  }
  return TestCaseResult(test_case_ptr, actual_result, actual_result_msg);
}

void PrintTestCaseResult(const TestCaseResult* test_case_result_ptr,
                         int testCaseIdx,
                         int testCaseCount) {

  bool skipped = test_case_result_ptr->skipped();
  bool success = test_case_result_ptr->success();

  if (skipped) {
    std::cout << "\033[33m";  // orange font
  } else if (success) {
    std::cout << "\033[32m";  // green  font
  } else {
    std::cout << "\033[31m";  // red    font
  }

  std::cout << "Test [" << testCaseIdx << " of " << testCaseCount  << "]:"
            << std::setw(60) << std::left
            << std::quoted(test_case_result_ptr->expression());
  if (skipped) {
    std::cout << "SKIPPED" << std::endl;
  } else if (success) {
    std::cout << "SUCCESS" << std::endl;
  } else {
    std::cout << "FAILED" << std::endl;
    std::cout << "  Actual Result: " << test_case_result_ptr->actual_result()
              << "  Expected Result: " << test_case_result_ptr->expected_result()
              << std::endl;
  }
  std::cout << "\033[m";
}

class SyntaxAnalyzerTest {
public:
  SyntaxAnalyzerTest(std::unique_ptr<SyntaxAnalyzer> sa):
    sa_(std::move(sa)) {}

  SyntaxAnalyzer* syntax_analyzer() const { return sa_.get(); }

  size_t total_test_count() const { return total_test_count_; }
  size_t success_test_count() const {return success_test_count_; }
  size_t skipped_test_count() const {return skipped_test_count_; }
  size_t failed_test_count() const {return failed_test_count_; }

  void total_test_count_increment() {
    total_test_count_++;
  }

  void success_test_count_increment() {
    success_test_count_++;
  }

  void skipped_test_count_increment() {
    skipped_test_count_++;
  }

  void failed_test_count_increment() {
    failed_test_count_++;
  }

private:
  std::unique_ptr<SyntaxAnalyzer> sa_;
  size_t total_test_count_  = 0;
  size_t success_test_count_ = 0;
  size_t skipped_test_count_ = 0;
  size_t failed_test_count_  = 0;
};

bool RunTestCases(SyntaxAnalyzerTest& sat,
                  const std::vector<TestCase>& test_cases,
                  int test_case_count,
                  int* test_case_idx_ptr) {

  bool ret = true;

  for (const auto& testCase : test_cases) {
    sat.total_test_count_increment();
    TestCaseResult test_case_result;
    if (testCase.available(sat.syntax_analyzer()->name())) {
      auto res = RunTestCase(sat.syntax_analyzer(), &testCase);
      if (res.success()) {
        sat.success_test_count_increment();
      } else {
        ret = false;
        sat.failed_test_count_increment();
      }
      test_case_result = std::move(res);
    }

    if (test_case_result.skipped()) {
      sat.skipped_test_count_increment();
    }

    PrintTestCaseResult(&test_case_result,
                        (*test_case_idx_ptr)++,
                        test_case_count);
  }
  return ret;
}

std::vector<TestCase> GeneratePositivTestCases() {
  std::vector<TestCase> r;

  r.push_back({"2+2", 4.0, "", {SchildtSyntaxAnalyzer::NAME,
                                SimplestSyntaxAnalyzer::NAME}});

  r.push_back({"2 + 8", 10, "", {SchildtSyntaxAnalyzer::NAME,
                                 SimplestSyntaxAnalyzer::NAME}});

  r.push_back({"    10  -  20  +  30  -22  ", -2.0, "",
                 {SchildtSyntaxAnalyzer::NAME,
                 SimplestSyntaxAnalyzer::NAME}});

  r.push_back({"10-3", 7.0, "", {SchildtSyntaxAnalyzer::NAME,
                                 SimplestSyntaxAnalyzer::NAME}});

  return r;
}

std::vector<TestCase> GenerateNegativeTestCases() {
  std::vector<TestCase> r;
  r.push_back({"22 + 400x", 0.0, "Unknown identifier: 400x",
                 {SchildtSyntaxAnalyzer::NAME
                  //SimplestSyntaxAnalyzer::NAME
                 }});

  r.push_back({"", 0.0, SyntaxAnalyzer::EMPTY_EXPRESSION_ERR_STR,
               {//SchildtSyntaxAnalyzer::NAME,
                SimplestSyntaxAnalyzer::NAME}});
  return r;
}

int main(int argc, char* argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  int ret = 0;

  std::cout << "Testing..." << std::endl;

  std::vector<SyntaxAnalyzerTest> v;
  v.emplace_back(std::make_unique<SchildtSyntaxAnalyzer>());
  v.emplace_back(std::make_unique<SimplestSyntaxAnalyzer>());

  auto positiveTestCases = GeneratePositivTestCases();
  auto negativeTestCases = GenerateNegativeTestCases();

  for (auto& sat : v) {
    std::cout << "Syntax Analyzer: " << sat.syntax_analyzer()->name() << std::endl;
    int testCaseCount = positiveTestCases.size() + negativeTestCases.size();
    int testCaseIdx = 1;

    std::cout << "Run positive test cases..." << std::endl;
    if (!RunTestCases(sat, positiveTestCases, testCaseCount, &testCaseIdx)) {
      ret = 1;
    }

    std::cout << "Run negative test cases..." << std::endl;
    if (!RunTestCases(sat, negativeTestCases, testCaseCount, &testCaseIdx)) {
      ret = 1;
    }
  }

  // Print final results
  for (const auto& sat : v) {
    std::cout << "Syntax analyzer: " << std::setw(30) << std::left
              << sat.syntax_analyzer()->name()
              << " Total: "   << std::setw(2) << sat.total_test_count()
              << " Success: " << std::setw(2) << sat.success_test_count()
              << " Skipped: " << std::setw(2) << sat.skipped_test_count()
              << " Failed: "  << std::setw(2) << sat.failed_test_count()
              << std::endl;
  }

  if (ret == 0) {
    std::cout << "SUCCESS" << std::endl;
  }

  return ret;
}
