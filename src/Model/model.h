#ifndef SMARTCALC_SRC_MODEL_MODEL_H_
#define SMARTCALC_SRC_MODEL_MODEL_H_

#include <algorithm>
#include <cmath>
#include <stack>
#include <string>

namespace awfl {
enum { OK, ERROR, INF };

typedef enum {
  NONE,
  ADD,
  SUB,
  MULT,
  DIV,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} Function;

typedef enum {
  VARIABLE,
  NUMBER,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  ADD_SUB,
  MULT_DIV,
  POW,
  UNARY,
  FUNCTION
} Token;

typedef struct {
  Token type;
  double number;
  Function func;
} StackNode;

class Model {
 public:
  Model() = default;

  Model(double var, std::string eq) noexcept {
    this->var = var;
    this->eq = eq;
    iter = (this->eq).begin();
  }

  ~Model() = default;

  void set(std::string eq, double var = 0.0) noexcept {
    this->var = var;
    this->eq = eq;
    iter = (this->eq).begin();
  }

  double get() const noexcept { return result; }

  std::pair<int, double> calculateReversePN();

 private:
  // Data
  double var = 0.0;
  std::string eq;
  std::string::iterator iter;

  double result = 0.0;

  // Postfix and prefix PN stacks
  std::stack<StackNode> postfix;
  std::stack<StackNode> prefix;

  // Helper functions
  void clearStack();
  void reverseStack();

  void stringToStack();
  double readNumber();
  void pushToStack(std::stack<StackNode> &temp, StackNode &node, int shift);
  int binaryOperation(std::stack<StackNode> &calculationStack);
  int unaryOperation(std::stack<StackNode> &calculationStack);
};
}  // namespace awfl

#endif  // SMARTCALC_SRC_MODEL_MODEL_H_
