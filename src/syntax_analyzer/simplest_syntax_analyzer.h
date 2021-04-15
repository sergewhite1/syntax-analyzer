#ifndef SIMPLEST_SYNTAX_ANALYZER_H_
#define SIMPLEST_SYNTAX_ANALYZER_H_

#include "syntax_analyzer.h"

class SimplestSyntaxAnalyzer : public SyntaxAnalyzer {
public:
  // SyntaxAnalyzer interface
  virtual double getValue() override;
  std::string name() const override {
    return "SimplestSyntaxAnalyzer";
  }

  static const std::string NAME;
};


#endif // ! SIMPLEST_SYNTAX_ANALYZER_H_
