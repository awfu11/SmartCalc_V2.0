#include "model.h"

namespace awfl {
void Model::clearStack() {
  while (postfix.size()) {
    postfix.pop();
  }
}

void Model::reverseStack() {
  while (prefix.size()) {
    postfix.push(prefix.top());
    prefix.pop();
  }
}

std::pair<int, double> Model::calculateReversePN() {
  stringToStack();
  std::stack<StackNode> calculationStack;
  int flag = OK;
  while (postfix.size()) {
    StackNode node = postfix.top();
    if (node.type == NUMBER) {
      postfix.pop();
      calculationStack.push(node);
    } else if (node.type >= ADD_SUB && node.type <= POW) {
      if ((flag = binaryOperation(calculationStack)) != OK) {
        break;
      }
    } else if (node.type >= UNARY) {
      if ((flag = unaryOperation(calculationStack)) != OK) {
        break;
      }
    } else {
      postfix.pop();
      StackNode n = {NUMBER, var, NONE};
      calculationStack.push(n);
    }
  }
  if (!calculationStack.empty()) {
    result = calculationStack.top().number;
  }
  clearStack();
  return {flag, result};
}

int Model::binaryOperation(std::stack<StackNode> &calculationStack) {
  double secondNumber = calculationStack.top().number;
  calculationStack.pop();

  double firstNumber = calculationStack.top().number;
  calculationStack.pop();

  StackNode node = postfix.top();
  double result = 0.0;

  if (node.func == ADD) {
    result = firstNumber + secondNumber;
  } else if (node.func == SUB) {
    result = firstNumber - secondNumber;
  } else if (node.func == MULT) {
    result = firstNumber * secondNumber;
  } else if (node.func == DIV) {
    result = firstNumber / secondNumber;
  } else if (node.func == MOD) {
    result = std::fmod(firstNumber, secondNumber);
  } else if (node.type == POW) {
    result = std::pow(firstNumber, secondNumber);
  }

  if (std::isinf(result)) {
    return INF;
  } else if (result != result) {
    return ERROR;
  }

  postfix.pop();

  StackNode n = {NUMBER, result, NONE};
  postfix.push(n);

  return OK;
}

int Model::unaryOperation(std::stack<StackNode> &calculationStack) {
  double number = calculationStack.top().number;
  calculationStack.pop();

  StackNode node = postfix.top();
  double result = 0.0;

  if (node.type == UNARY) {
    result = -1.0 * number;
  } else if (node.func == COS) {
    result = cos(number);
  } else if (node.func == SIN) {
    result = sin(number);
  } else if (node.func == TAN) {
    result = tan(number);
  } else if (node.func == ACOS) {
    result = acos(number);
  } else if (node.func == ASIN) {
    result = asin(number);
  } else if (node.func == ATAN) {
    result = atan(number);
  } else if (node.func == LN) {
    result = log(number);
  } else if (node.func == LOG) {
    result = log10(number);
  } else if (node.func == SQRT) {
    result = sqrt(number);
  }

  if (std::isinf(result)) {
    return INF;
  } else if (result != result) {
    return ERROR;
  }

  postfix.pop();

  StackNode n = {NUMBER, result, NONE};
  postfix.push(n);

  return OK;
}

void Model::pushToStack(std::stack<StackNode> &temp, StackNode &node,
                        int shift) {
  while (temp.size() && (temp.top()).type >= node.type) {
    StackNode n = temp.top();
    prefix.push(n);
    temp.pop();
  }

  if (temp.size() && node.type == RIGHT_PARENTHESIS) {
    temp.pop();
  } else {
    temp.push(node);
  }
  iter += shift;
}

double Model::readNumber() {
  double number = 0.0;
  if (*iter == 'e') {
    number = M_E;
    ++iter;
  } else if (!eq.compare(iter - eq.begin(), 2, "pi")) {
    number = M_PI;
    iter += 2;
  } else {
    std::string temp({iter, eq.end()});
    auto it = iter;
    auto isSign = [](auto &c) { return (c == '+' || c == '-'); };
    while (it != eq.end() &&
           (std::isdigit(*it) || *it == '.' ||
            (isSign(*it) && *(it - 1) == 'e') || *it == 'e')) {
      ++it;
    }
    number = std::stold(temp);
    iter = it;
  }
  return number;
}

void Model::stringToStack() {
  std::stack<StackNode> temp;
  StackNode node;
  bool checkUnary = true;
  while (iter != eq.end()) {
    if (std::isdigit(*iter) || !eq.compare(iter - eq.begin(), 2, "pi") ||
        *iter == 'e') {
      node = {NUMBER, readNumber(), NONE};
      prefix.push(node);
      checkUnary = false;
    } else if (*iter == 'x' || *iter == 'X') {
      node = {VARIABLE, 0.0, NONE};
      prefix.push(node);
      checkUnary = false;
      ++iter;
    } else if (*iter == '(') {
      node = {LEFT_PARENTHESIS, 0.0, NONE};
      temp.push(node);
      ++iter;
      checkUnary = true;
    } else if (*iter == ')') {
      node = {RIGHT_PARENTHESIS, 0.0, NONE};
      pushToStack(temp, node, 1);
    } else if (*iter == '-') {
      node = {(checkUnary ? UNARY : ADD_SUB), 0.0, (checkUnary ? NONE : SUB)};
      pushToStack(temp, node, 1);
      checkUnary = checkUnary ? false : true;
    } else if (*iter == '+') {
      if (!checkUnary) {
        node = {ADD_SUB, 0.0, ADD};
        pushToStack(temp, node, 1);
      } else {
        ++iter;
      }
      checkUnary = checkUnary ? false : true;
    } else if (*iter == '/') {
      node = {MULT_DIV, 0.0, DIV};
      pushToStack(temp, node, 1);
      checkUnary = true;
    } else if (*iter == '*') {
      node = {MULT_DIV, 0.0, MULT};
      pushToStack(temp, node, 1);
      checkUnary = true;
    } else if (*iter == '^') {
      node = {POW, 0.0, NONE};
      pushToStack(temp, node, 1);
      checkUnary = true;
    } else if (*iter == '%' || !eq.compare(iter - eq.begin(), 3, "mod")) {
      node = {MULT_DIV, 0.0, MOD};
      pushToStack(temp, node, (*iter == '%' ? 1 : 3));
      checkUnary = true;
    } else if (!eq.compare(iter - eq.begin(), 3, "cos")) {
      node = {FUNCTION, 0.0, COS};
      pushToStack(temp, node, 3);
    } else if (!eq.compare(iter - eq.begin(), 3, "sin")) {
      node = {FUNCTION, 0.0, SIN};
      pushToStack(temp, node, 3);
    } else if (!eq.compare(iter - eq.begin(), 3, "tan")) {
      node = {FUNCTION, 0.0, TAN};
      pushToStack(temp, node, 3);
    } else if (!eq.compare(iter - eq.begin(), 4, "acos")) {
      node = {FUNCTION, 0.0, ACOS};
      pushToStack(temp, node, 4);
    } else if (!eq.compare(iter - eq.begin(), 4, "asin")) {
      node = {FUNCTION, 0.0, ASIN};
      pushToStack(temp, node, 4);
    } else if (!eq.compare(iter - eq.begin(), 4, "atan")) {
      node = {FUNCTION, 0.0, ATAN};
      pushToStack(temp, node, 4);
    } else if (!eq.compare(iter - eq.begin(), 2, "ln")) {
      node = {FUNCTION, 0.0, LN};
      pushToStack(temp, node, 2);
    } else if (!eq.compare(iter - eq.begin(), 3, "log")) {
      node = {FUNCTION, 0.0, LOG};
      pushToStack(temp, node, 3);
    } else if (!eq.compare(iter - eq.begin(), 4, "sqrt")) {
      node = {FUNCTION, 0.0, SQRT};
      pushToStack(temp, node, 4);
    } else {
      ++iter;
    }
  }
  while (temp.size()) {
    prefix.push(temp.top());
    temp.pop();
  }
  reverseStack();
}
}  // namespace awfl
