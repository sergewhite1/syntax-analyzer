#include "syntax_analyzer.h"

#include <sstream>

void SyntaxAnalyzer::setExpression(const std::string& expression) {
  expression_ = expression;
}

SyntaxAnalyzerException::SyntaxAnalyzerException(const char* message)
 : message_(message) {}

 SyntaxAnalyzerException
 SyntaxAnalyzerException::CreateForUnknownIdentifier(const char* unknown_identifier) {

  std::stringstream ss;
  ss << "Unknown identifier: " << unknown_identifier;
  return SyntaxAnalyzerException(ss.str().c_str());
}

const char* SyntaxAnalyzerException::what() const noexcept {
  return message_.c_str();
 }