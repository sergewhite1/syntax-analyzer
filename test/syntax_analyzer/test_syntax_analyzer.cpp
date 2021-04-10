#include <cstring>
#include <memory>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../../src/syntax_analyzer/schildt/schildt_syntax_analyzer.h"
#include "../../src/syntax_analyzer/simplest_syntax_analyzer.h"

#include "../same_value.h"

#define UNUSED(x) (void)(x)

void printHelp() {
  std::cout << "HELP:" << std::endl;
  std::cout << "./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase Add"
            << std::endl;

}

struct PositiveTestCase {
  std::string expression;
  double expected_result = 0;

  PositiveTestCase(const char* __expression,
                   double __expected_result):

                  expression(__expression),
                  expected_result(__expected_result) {}
};

struct NegativeTestCase {
  std::string expression;
  std::string expected_result_error_msg;

  NegativeTestCase(const char* __expression,
                   const char* __expected_result_error_msg):

                   expression(__expression),
                   expected_result_error_msg(__expected_result_error_msg) {}
};

void RunPositiveTestCase(SyntaxAnalyzer* sa_ptr,
                         const PositiveTestCase* test_case_ptr,
                         bool* success_ptr,
                         double* actual_result_ptr) {
  sa_ptr->setExpression(test_case_ptr->expression);
  *actual_result_ptr = sa_ptr->getValue();
  *success_ptr = same_value(*actual_result_ptr, test_case_ptr->expected_result);
}

void RunNegativeTestCase(SyntaxAnalyzer* sa_ptr,
                         const NegativeTestCase* testCase_ptr,
                         bool* success,
                         std::string* actual_result_err_msg) {

  actual_result_err_msg->clear();
  try {
    sa_ptr->setExpression(testCase_ptr->expression);
    sa_ptr->getValue();
  } catch (const SyntaxAnalyzerException& e) {
     *actual_result_err_msg = e.what();
  }
  *success = *actual_result_err_msg == testCase_ptr->expected_result_error_msg;
}

template <typename ResultType>
void PrintTestCaseResult(int testCaseIdx,
                         int testCaseCount,
                         const std::string& expression,
                         bool success,
                         const ResultType& actual_result,
                         const ResultType& expected_result) {

  std::cout << (success ? "\033[32m" : "\033[31m");

  std::cout << "Test [" << testCaseIdx << " of " << testCaseCount  << "]:"
            << std::setw(60) << std::left << std::quoted(expression)
            << (success ? "SUCCESS" : "FAILED") << std::endl;
  if (!success) {
    std::cout << "  Actual Result: " << actual_result
              << "  Expected Result: " << expected_result
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

int main(int argc, char* argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  int ret = 0;

  std::cout << "Testing..." << std::endl;

  std::vector<SyntaxAnalyzerTest> v;
  v.emplace_back(std::make_unique<SchildtSyntaxAnalyzer>());
  v.emplace_back(std::make_unique<SimplestSyntaxAnalyzer>());

  std::vector<PositiveTestCase> positiveTestCases;
  std::vector<PositiveTestCase>& P = positiveTestCases;
  P.emplace_back("2+2", 4.0);
  P.emplace_back("2 + 8", 10);
  P.emplace_back("    10  -  20  +  30  -22  ", -2.0);
  P.emplace_back("10-3", 7.0);

  std::vector<NegativeTestCase> negativeTestCases;
  std::vector<NegativeTestCase>& N = negativeTestCases;
  N.emplace_back("22 + 400x", "Unknown identifier: 400x");
  N.emplace_back("", "");

  for (auto& sat : v) {
    std::cout << "Syntax Analyzer: " << sat.syntax_analyzer()->name() << std::endl;
    int testCaseIdx = 1;
    int testCaseCount = positiveTestCases.size() + negativeTestCases.size();

    std::cout << "Run positive test cases..." << std::endl;
    for (const auto& testCase : positiveTestCases) {
      sat.total_test_count_increment();
      bool success = false;
      double actual_result = 0;
      RunPositiveTestCase(sat.syntax_analyzer(),
                          &testCase,
                          &success,
                          &actual_result);
      if (success) {
        sat.success_test_count_increment();
      } else
      {
        ret = 1;
        sat.failed_test_count_increment();
      }
      PrintTestCaseResult(testCaseIdx++,
                          testCaseCount,
                          testCase.expression,
                          success,
                          actual_result,
                          testCase.expected_result);
    }

    std::cout << "Run negative test cases..." << std::endl;
    for (const auto& testCase : negativeTestCases) {
      sat.total_test_count_increment();

      //TODO: Negative unit tests for SimplestSyntaxAnalyzer
      if (sat.syntax_analyzer()->name() == "SimplestSyntaxAnalyzer") {
        sat.skipped_test_count_increment();
        continue;
      }

      bool success = false;
      std::string actual_result_err_msg;
      RunNegativeTestCase(sat.syntax_analyzer(),
                          &testCase,
                          &success,
                          &actual_result_err_msg);
      if (success) {
        sat.success_test_count_increment();
      } else
      {
        ret = 1;
        sat.failed_test_count_increment();
      }
      PrintTestCaseResult(testCaseIdx++,
                          testCaseCount,
                          testCase.expression,
                          success,
                          actual_result_err_msg,
                          testCase.expected_result_error_msg);
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
