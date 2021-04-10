#include "recursive_syntax_analyzer.h"

#include <cstring>
#include <sstream>

// For debug
#pragma GCC push_options
#pragma GCC optimize ("O0")

double RecursiveSyntaxAnalyzer::getValue() {
  return parse(expression_.c_str());
}

double RecursiveSyntaxAnalyzer::parse(const char* expr_ptr) {
  const char* tmp;

  // find syntax rule: <expression> + <expression>
  tmp = expr_ptr;
  while(*tmp) {
    if (*tmp == '+') {
      size_t pos = tmp - expr_ptr;
      std::string expr1(expr_ptr, pos);
      double a = parse(expr1.c_str());

      std::string expr2(++tmp);
      double b = parse(expr2.c_str());
      double ret = a + b;
      return ret;
    }
    tmp++;
  }

  // find syntax rule: <number>
  const char* tmp2 = expr_ptr;
  while(isspace(*tmp2)) {
    tmp2++;
  }
  tmp = tmp2;
  while(*tmp) {
    if (!isdigit(*tmp)) {
      std::stringstream message;
      message << "Unknown identifier: \"" << expr_ptr << "\"";
      throw SyntaxAnalyzerException(message.str().c_str());
    }
    tmp++;
  }
  double ret = std::atoi(tmp2);
  return ret;
}