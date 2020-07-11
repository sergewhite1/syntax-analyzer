#ifndef SYNTAX_ANALYZER_H_
#define SYNTAX_ANALYZER_H_

#include <string>

class SyntaxAnalyzer {
public:
  SyntaxAnalyzer() = default;
  explicit SyntaxAnalyzer(const std::string& expression): 
    expression_(expression) {}

  virtual ~SyntaxAnalyzer() = default;

  std::string expression() const { return expression_; }

  virtual void setExpression(const std::string& expression)=0;
  virtual double getValue()=0;

protected:
  std::string expression_;
};

#endif // ! SYNTAX_ANALYZER_H_
