#ifndef SCHILDT_SYNTAX_ANALYZER_H_
#define SCHILDT_SYNTAX_ANALYZER_H_

#include "schildt/parser.h"
#include "syntax_analyzer/syntax_analyzer.h"

class SchildtSyntaxAnalyzer : public SyntaxAnalyzer {
public:
  // SyntaxAnalyzer interface
  virtual double getValue() override;
    std::string name() const override {
    return SchildtSyntaxAnalyzer::NAME;
  }

  static const std::string NAME;

private:
  schildt::parser parser_;
};


#endif // ! SCHILDT_SYNTAX_ANALYZER_H_

