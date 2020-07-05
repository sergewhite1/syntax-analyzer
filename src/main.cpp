#include <iostream>

#include "schildt/parser.h"

int main() {
  std::cout << "syntax-analyzer demo." << std::endl;

  char exp[] = "AAA";

  schildt::parser parser;

  double eval_exp = parser.eval_exp(exp);
  std::cout << "exp=      " << exp << std::endl;
  std::cout << "eval_exp= " << eval_exp << std::endl;

  return 0;
}
