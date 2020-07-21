// ./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase Add
// ./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase AddSubtract-1
// ./test-syntax-analyzer --class SimplestSyntaxAnalyzer --testCase AddSubtract-2

#include <cstring>
#include <memory>
#include <iostream>

#include "../../src/syntax_analyzer/syntax_analyzer.h"
#include "../../src/syntax_analyzer/simplest_syntax_analyzer.h"

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
        if (i + 1 <= argc) {
          std::cout << "CommandLineArgs: Empty class name!" << std::endl;
          return false;
        }
        className_ = argv[i + 1];
      }
    }
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

int main(int argc, char* argv[]) {
  CommandLineArgs commandLineArgs;
  if (commandLineArgs.init(argc, argv) == false) {
    printHelp();
    return 1;
  }

  std::unique_ptr<SyntaxAnalyzer> syntax_analyzer;
  
  if (strcmp(commandLineArgs.className(), "SimplestSyntaxAnalyzer") == 0) {
    syntax_analyzer.reset(new SimplestSyntaxAnalyzer());
  } else {
    std::cerr << "Unexpected class name: " << commandLineArgs.className() << std::endl;
    return 1;
  }

  return 1;
}
