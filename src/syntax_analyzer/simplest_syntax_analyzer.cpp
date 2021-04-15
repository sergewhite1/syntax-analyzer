#include "simplest_syntax_analyzer.h"

#include <sstream>

const std::string SimplestSyntaxAnalyzer::NAME = "SimplestSyntaxAnalyzer";

double SimplestSyntaxAnalyzer::getValue() {
  if (expression_.empty()) {
    throw SyntaxAnalyzerException(
            SimplestSyntaxAnalyzer::EMPTY_EXPRESSION_ERR_STR);
  }

  double operand1, operand2;
  char opcode;
  size_t curr_pos  = 0;
  size_t opcode_pos = 0;
  bool operand1_defined = false;

  while (true) {
    opcode_pos = expression_.find_first_of("+-", curr_pos);
    std::string value_str = expression_.substr(curr_pos, opcode_pos);
    if (operand1_defined) {
      operand2 = std::atof(value_str.c_str());
      switch (opcode) {
        case '+':
          operand1 += operand2;
        break;

        case '-':
          operand1 -= operand2;
        break;

        default:
          {
            std::stringstream ss;
            ss << "Unexpected opcode '" << opcode << "' in expression: " << expression_ << std::endl;
            ss << "Available opcode: '+', '-'." << std::endl;
            throw SyntaxAnalyzerException(ss.str().c_str());
          }
      }
    } else {
      operand1 = std::atof(value_str.c_str());
      operand1_defined = true;
    }

    if (opcode_pos == std::string::npos) {
      break;
    }

    opcode = expression_[opcode_pos];
    curr_pos = opcode_pos + 1;
  }

  return operand1;
}
