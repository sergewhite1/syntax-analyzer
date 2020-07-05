#ifndef SCHILDT_PARSER_H_
#define SCHILDT_PARSER_H_

// Simple Syntax Analyzer from book Herbert Schildt 
// C++: The Complete Reference (4th Edition).

namespace schildt {

  enum types {DELIMETER = 1, VARIABLE, NUMBER};

  class parser {
    char *exp_ptr = nullptr;
    char token[80];
    char tok_type;

    void eval_exp2(double &result);
    void eval_exp3(double &result);
    void eval_exp4(double &result);
    void eval_exp5(double &result);
    void eval_exp6(double &result);
    void atom(double &result);
    void get_token();
    void serror(int error);
    int isdelim(char c);
  public:
    double eval_exp(char *exp);
  };

} // namespace schildt

#endif // ! SCHILDT_PARSER_H_
