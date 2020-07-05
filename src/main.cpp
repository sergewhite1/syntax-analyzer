#include <iostream>

#include "schildt/parser.h"

int main() {
  std::cout << "Syntax-analyzer demo." << std::endl;
  std::cout << "For end of work input dot." << std::endl;

  schildt::parser parser;

  char expstr[80];

  for (;;) {
    std::cout << "Input expression: ";
    std::cin.getline(expstr, 79);
    if(*expstr == '.') break;
    std::cout << "Answer: " << parser.eval_exp(expstr) << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
