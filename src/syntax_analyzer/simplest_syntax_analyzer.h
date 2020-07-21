#ifndef SIMPLEST_SYNTAX_ANALYZER_H_
#define SIMPLEST_SYNTAX_ANALYZER_H_

#include "syntax_analyzer.h"

class SimplestSyntaxAnalyzer : public SyntaxAnalyzer {
public:
  // SyntaxAnalyzer interface
  virtual double getValue() override;
};


#endif // ! SIMPLEST_SYNTAX_ANALYZER_H_
