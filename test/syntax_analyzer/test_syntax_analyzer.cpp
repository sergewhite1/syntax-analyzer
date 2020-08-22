// ./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase Add
// ./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase AddSubtract-1
// ./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase AddSubtract-2

#include <cstring>
#include <memory>
#include <iostream>

#include "../../src/syntax_analyzer/syntax_analyzer.h"
#include "../../src/syntax_analyzer/simplest_syntax_analyzer.h"

#include "../same_value.h"

class CommandLineArgs {
public:
  const char* className() const {
    return className_;
  }

  const char* testCase() const {
    return testCase_;
  }

  bool init(int argc, const char * const * argv) {
    int i = 1;
    while (i < argc) {
      if (strcmp(argv[i], "--class") == 0) {
        if (i + 1 >= argc) {
          std::cout << "CommandLineArgs: Empty class name!" << std::endl;
          return false;
        }
        className_ = argv[i + 1];
        i+=2;
      } else if (strcmp(argv[i], "--testCase") == 0) {
        if (i + 1 >= argc) {
          std::cout << "CommandLineArgs: Empty test case name!" << std::endl;
          return false;
        }
        testCase_ = argv[i + 1];
        i += 2;
      }
    }

    if (className_ ==  nullptr || testCase_ == nullptr) {
      return false;
    }

    return true;
  }

private:
  const char *className_ = nullptr;
  const char *testCase_ = nullptr;
};

void printHelp() {
  std::cout << "HELP:" << std::endl;
  std::cout << "./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase Add" 
            << std::endl;

}

int TestCaseAdd(SyntaxAnalyzer* sa) {
  std::string expression = "2 + 8";
  sa->setExpression(expression);
  double val = sa->getValue();

  if (same_value(val, 10.0)) {
    return 0;
  }

  return 1;
}

int TestCaseEmptyExpression(SyntaxAnalyzer* sa) {
  int ret = 1;
  sa->setExpression("");
  try {
    sa->getValue();
  } catch (const SyntaxAnalyzerException& sa) {
    ret = 0;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  CommandLineArgs commandLineArgs;
  if (commandLineArgs.init(argc, argv) == false) {
    printHelp();
    return 1;
  }

  std::cout << "className: " << commandLineArgs.className() << std::endl;
  std::cout << "testCase : " << commandLineArgs.testCase() << std::endl;

  std::unique_ptr<SyntaxAnalyzer> syntax_analyzer;
  
  if (strcmp(commandLineArgs.className(), "SimplestSyntaxAnalyzer") == 0) {
    syntax_analyzer.reset(new SimplestSyntaxAnalyzer());
  } else {
    std::cerr << "Unexpected class name: " << commandLineArgs.className() << std::endl;
    return 1;
  }

  int ret = 1;

  const char * testCase = commandLineArgs.testCase();
  SyntaxAnalyzer * sa = syntax_analyzer.get();

  if (strcmp(testCase, "Add") == 0) {
    ret = TestCaseAdd(sa);
  } else if (strcmp(testCase, "EmptyExpression") == 0) {
    ret = TestCaseEmptyExpression(sa);
  } else {
    std::cerr << "Unexpected test case: " << commandLineArgs.testCase() << std::endl;
    return 1;
  }

  return ret;
}
