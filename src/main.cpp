#include <iostream>
#include <memory>

#include "syntax_analyzer/syntax_analyzer.h"
//#include "syntax_analyzer/simplest_syntax_analyzer.h"
#include "schildt_syntax_analyzer/schildt_syntax_analyzer.h"

int main() {
  std::cout << "Syntax-analyzer demo." << std::endl;
  std::cout << "For end of work input dot." << std::endl;

  std::unique_ptr<SyntaxAnalyzer> sa = 
    std::make_unique<SchildtSyntaxAnalyzer>();

  char expstr[80];

  for (;;) {
    std::cout << "Input expression: ";
    std::cin.getline(expstr, 79);
    if(*expstr == '.') break;
    sa->setExpression(std::string(expstr));
    std::cout << "Answer: " << sa->getValue() << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
