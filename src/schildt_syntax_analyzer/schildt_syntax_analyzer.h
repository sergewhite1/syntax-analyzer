#ifndef SCHILDT_SYNTAX_ANALYZER_H_
#define SCHILDT_SYNTAX_ANALYZER_H_

#include "schildt/parser.h"
#include "syntax_analyzer/syntax_analyzer.h"

class SchildtSyntaxAnalyzer : public SyntaxAnalyzer {
public:
  virtual void setExpression(const std::string& expression) override;
  virtual double getValue() override;

private:
  schildt::parser parser_;
};


#endif // ! SCHILDT_SYNTAX_ANALYZER_H_

