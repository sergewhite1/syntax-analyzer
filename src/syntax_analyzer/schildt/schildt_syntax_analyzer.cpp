#include "schildt_syntax_analyzer.h"

#include <cstring>
#include <memory>

double SchildtSyntaxAnalyzer::getValue() {
  size_t len = expression_.size();
  std::unique_ptr<char[]> str(new char [len + 1]);
  strcpy(str.get(), expression_.c_str());
  return parser_.eval_exp(str.get());
}


