#ifndef RECURSIVE_SYNTAX_ANALYZER_H_
#define RECURSIVE_SYNTAX_ANALYZER_H_

#include "syntax_analyzer.h"

class RecursiveSyntaxAnalyzer : public SyntaxAnalyzer {
public:
  virtual double getValue() override;

  enum class TokenType {UNKNOWN, NUMBER, OPERATION};

private:
  double parse(const char* expr);
};

#endif // ! RECURSIVE_SYNTAX_ANALYZER_H_