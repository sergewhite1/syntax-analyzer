#ifndef SYNTAX_ANALYZER_H_
#define SYNTAX_ANALYZER_H_

#include <exception>
#include <string>

class SyntaxAnalyzer {
public:
  SyntaxAnalyzer() = default;
  explicit SyntaxAnalyzer(const std::string& expression):
    expression_(expression) {}

  virtual ~SyntaxAnalyzer() = default;

  std::string expression() const { return expression_; }

  virtual void setExpression(const std::string& expression);
  virtual double getValue()=0;
  virtual std::string name() const =0;

  static const char* EMPTY_EXPRESSION_ERR_STR;

protected:
  std::string expression_;
};

class SyntaxAnalyzerException : public std::exception {
public:
  explicit SyntaxAnalyzerException(const char* message);

  static SyntaxAnalyzerException CreateForUnknownIdentifier(const char* unknown_identifier);

  // std::excpetion interface
  virtual const char* what() const noexcept override;

private:
  const std::string message_;
};

#endif // ! SYNTAX_ANALYZER_H_
