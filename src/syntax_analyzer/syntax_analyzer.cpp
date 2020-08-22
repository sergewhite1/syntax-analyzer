#include "syntax_analyzer.h"

void SyntaxAnalyzer::setExpression(const std::string& expression) {
  expression_ = expression;
}

SyntaxAnalyzerException::SyntaxAnalyzerException(const char* message)
 : message_(message) {}

const char* SyntaxAnalyzerException::what() const noexcept {
  return message_.c_str();
 }