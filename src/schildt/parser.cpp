#include "parser.h"

#include <cstring>
#include <iostream>

namespace schildt {

  double parser::eval_exp(char *exp) {
    double result;

    exp_ptr = exp;

    get_token();

    if (!*token) {
      serror(2);
      return 0.0;
    }

    eval_exp2(result);

    if(*token) {
      serror(0);
    }

    return result;
  }

  void parser::eval_exp2(double &result) {
    char op;
    double temp;

    eval_exp3(result);

    while((op = *token) == '+'|| op == '-') {
      get_token();
      eval_exp3(temp);
      switch(op) {
        case '-':
          result = result - temp;
          break;
        case '+':
          result = result + temp;
          break;
      }

    }
  }

  void parser::eval_exp3(double &result) {
    char op;
    double temp;

    eval_exp4(result);
    while((op = *token) == '*' || op == '/' || op == '%') {
      get_token();
      eval_exp4(temp);
      switch(op) {
        case '*':
        result = result * temp;
          break;

        case '/':
          result = result / temp;
          break;

        case '%':
          result = (int) result % (int) temp;
          break;
      }
    }
  }

  void parser::eval_exp4(double &result) {
    double temp, ex;
    int t;

    eval_exp5(result);

    if (*token == '^') {
      get_token();
      eval_exp4(temp);
      ex = result;
      if (temp == 0.0) {
        result = 1.0;
        return;
      }
      for (t=(int)temp-1; t > 0; --t) result = result * (double)ex;
    }
  }

  void parser::eval_exp5(double &result) {
    char op;
    op = 0;

    if (((tok_type == DELIMETER) && *token == '+') || *token == '-' ) {
      op = *token;
      get_token();
    }
    eval_exp6(result);
    if (op == '-') result = -result;
  }

  void parser::eval_exp6(double &result) {
    if ((*token == '(')) {
      get_token();
      eval_exp2(result);
      if(*token == ')') {
        serror(1);
      }
      get_token();
    }
    else {
      atom(result);
    }
  }

  void parser::atom(double &result) {
    switch(tok_type) {
      case NUMBER:
        result = atof(token);
        get_token();
        return;

      default:
        serror(0);
    }
  }

  void parser::serror(int error) {
    static const char *e[] = {
      "Syntax error",
      "Bad bracket balance",
      "Empty expression"
    };
    std::cout << e[error] << std::endl;
  }

  void parser::get_token() {
    char * temp;
    tok_type = 0;
    temp = token;
    *temp = '\0';

    if (!*exp_ptr) return;

    while(isspace(*exp_ptr)) ++exp_ptr;

    if (strchr("+-*/%^=()", *exp_ptr)) {
      tok_type = DELIMETER;
      *temp++ = *exp_ptr++;
    } else if(isalpha(*exp_ptr)) {
      while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
      tok_type = VARIABLE;
    } else if (isdigit(*exp_ptr)) {
      while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
      tok_type = NUMBER;
    }

    *temp = '\0';
  }

  int parser::isdelim(char c) {
    if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0 ) {
      return 1;
    }
    return 0;
  }

} // namespace schildt
