#include "s21_model.h"
using namespace s21;

double Model::Calculator(std::string input, std::string x) {
  CheckInput(input);
  SetInput(input);
  SetX(x);
  result_ = MainCalculation();
  return result_;
}

double Model::MainCalculation() {
  StringToLexeme();
  PolTransform();  // трансформируем в польскую нотацию
  PolCalc();       // вычисляем польскую нотацию
  return result_;
}

Model::Lexeme Model::CheckLexeme(int *i, int *unar) {
  Lexeme res;
  if (Input_[*i] == '+') {
    *i += 1;
    if (*unar) {
      res = {0, S21_UN_PLUS, 1};
    } else {
      res = {0, S21_PLUS, 1};
    }
  } else if (Input_[*i] == '-') {
    *i += 1;
    if (*unar) {
      res = {0, S21_UN_MINUS, 1};
    } else {
      res = {0, S21_MINUS, 1};
    }
  } else if (Input_[*i] == '/') {
    *i += 1;
    res = {0, S21_DIV, 2};
  } else if (Input_[*i] == '*') {
    *i += 1;
    res = {0, S21_MUL, 2};
  } else if (Input_[*i] == '^') {
    *i += 1;
    res = {0, S21_POW, 3};
  } else if (Input_[*i] == 'X') {
    *i += 1;
    res = {X_, S21_X, 0};
    *unar = 0;
  } else if (!Input_.compare(*i, 4, "sin(")) {
    *i += 4;
    res = {0, S21_SIN, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 4, "cos(")) {
    *i += 4;
    res = {0, S21_COS, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 4, "tan(")) {
    *i += 4;
    res = {0, S21_TAN, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 5, "acos(")) {
    *i += 5;
    res = {0, S21_ACOS, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 5, "asin(")) {
    *i += 5;
    res = {0, S21_ASIN, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 5, "atan(")) {
    *i += 5;
    res = {0, S21_ATAN, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 5, "sqrt(")) {
    *i += 5;
    res = {0, S21_SQRT, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 3, "ln(")) {
    *i += 3;
    res = {0, S21_LN, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 4, "log(")) {
    *i += 4;
    res = {0, S21_LOG, 4};
    *unar = 1;
  } else if (!Input_.compare(*i, 3, "mod")) {
    *i += 3;
    res = {0, S21_MOD, 2};
  } else if (Input_[*i] == '(') {
    *i += 1;
    res = {0, S21_LEFT_SCOBE, 4};
    *unar = 1;
  } else if (Input_[*i] == ')') {
    *i += 1;
    res = {0, S21_RIGHT_SCOBE, 5};
    *unar = 0;
  } else if (isdigit(Input_[*i])) {
    double value = atof(&Input_[*i]);
    while (isdigit(Input_[*i]) || (Input_[*i] == '.'))
      *i += 1;  // пока символ цифра или точка двигаем счетчик
    res = {value, S21_NUMBER, 0};
    *unar = 0;
  } else {
  }
  return res;
}

void Model::StringToLexeme() {
  int i = 0, len = Input_.size(), unar = 1;
  while (i < len) {
    Infix_.push_back(CheckLexeme(&i, &unar));
  }
}

void Model::PolTransform() {
  std::stack<Lexeme> Operators_;
  auto it = Infix_.begin();
  while (it != Infix_.end()) {
    int prior = it->priority;
    if (prior >= 1 && prior <= 3) {
      if (it->type == S21_UN_MINUS || it->type == S21_UN_PLUS) {
        Operators_.push(*it);
      } else {
        while (!(Operators_.empty()) && Operators_.top().priority >= prior &&
               Operators_.top().priority != 4) {
          Postfix_.push_back(Operators_.top());
          Operators_.pop();
        }
        Operators_.push(*it);
      }
    } else if (prior == 4) {
      Operators_.push(*it);
    } else if (prior == 5) {
      while (Operators_.top().priority != 4) {
        Postfix_.push_back(Operators_.top());
        Operators_.pop();
      }
      if (Operators_.top().type >= 7 && Operators_.top().type <= 15) {
        Postfix_.push_back(Operators_.top());
      }
      Operators_.pop();  //??
    } else if (prior == 0) {
      Postfix_.push_back(*it);
    }
    ++it;
  }
  Infix_.clear();
  while (!(Operators_.empty())) {
    Postfix_.push_back(Operators_.top());
    Operators_.pop();
  }
}

void Model::PolCalc() {
  std::stack<Lexeme> BufStack;
  double value = 0;
  auto it = Postfix_.begin();

  while (it != Postfix_.end()) {
    if (it->priority == 0) {  // number
      BufStack.push(*it);
    } else {  // operator
      value = BufStack.top().value;
      if (it->type <= 6) {  // binary
        // value = BufStack.top().value;
        BufStack.pop();
        BufStack.top().value =
            BinaryOperation(BufStack.top().value, value, it->type);
      } else {  //  unary
        BufStack.top().value = UnaryOperation(value, it->type);
      }
    }
    ++it;
  }
  Postfix_.clear();
  if (!(BufStack.top().value == BufStack.top().value))
    throw std::invalid_argument("Ошибка! Результат вычислений nan!\n");  //?
  if (std::isinf(BufStack.top().value))
    throw std::invalid_argument("Ошибка! Результат вычислений inf или -inf!\n");

  result_ = BufStack.top().value;
}

double Model::UnaryOperation(double a, s21_lexeme op) {
  double result = 0;
  if (op == 7) {
    result = cosl(a);
  } else if (op == 8) {
    result = sinl(a);
  } else if (op == 9) {
    result = tanl(a);
  } else if (op == 10) {
    result = acosl(a);
  } else if (op == 11) {
    result = asinl(a);
  } else if (op == 12) {
    result = atanl(a);
  } else if (op == 13) {
    result = sqrtl(a);
  } else if (op == 14) {
    result = logl(a);  //  ln
  } else if (op == 15) {
    result = log10l(a);  // log
  } else if (op == 19) {
    result = 0 + a;
  } else if (op == 20) {
    result = 0 - a;
  }
  return result;
}

double Model::BinaryOperation(double a, double b, s21_lexeme op) {
  double result = 0;
  if (op == 1) {
    result = a + b;
  } else if (op == 2) {
    result = a - b;
  } else if (op == 4) {
    result = a * b;
  } else if (op == 3) {
    result = a / b;
  } else if (op == 5) {
    result = pow(a, b);
  } else if (op == 6) {
    result = fmodl(a, b);
  }
  return result;
}

void Model::SetInput(std::string input) { this->Input_ = input; }

void Model::SetX(std::string x) { this->X_ = SetDouble(x); }

double Model::SetDouble(std::string x) {
  ErrorXY(x);
  return atof(x.c_str());
}

bool s21::IsOperator(char sym) {
  bool res = false;
  if (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^')
    res = true;
  return res;
}

bool s21::IsBracket(char sym) {
  bool res = false;
  if (sym == '(' || sym == ')') res = true;
  return res;
}

bool s21::IsFunBegin(char sym) {
  bool res = false;
  if (sym == 's' || sym == 'c' || sym == 't' || sym == 'a' || sym == 'l')
    res = true;
  return res;
}

void s21::SkipNumber(std::string input, int *i) {
  int dot = 0;
  if (input[*i] != 'X') {
    while (isdigit(input[*i]) || (input[*i] == '.' && !dot)) {
      if (input[*i] == '.') dot = 1;
      (*i)++;
    }
  } else {
    (*i)++;
  }
  if (isdigit(input[*i]) || input[*i] == 'X' || IsFunBegin(input[*i]) ||
      input[*i] == '(')
    throw std::invalid_argument("Неверно составленное выражение!!!\n");
}

void s21::SkipFun(std::string input, int *i) {
  if (!input.compare(*i, 4, "sin(")) {
    *i += 3;
  } else if (!input.compare(*i, 4, "cos(")) {
    *i += 3;
  } else if (!input.compare(*i, 4, "tan(")) {
    *i += 3;
  } else if (!input.compare(*i, 5, "asin(")) {
    *i += 4;
  } else if (!input.compare(*i, 5, "acos(")) {
    *i += 4;
  } else if (!input.compare(*i, 5, "atan(")) {
    *i += 4;
  } else if (!input.compare(*i, 5, "sqrt(")) {
    *i += 4;
  } else if (!input.compare(*i, 3, "ln(")) {
    *i += 2;
  } else if (!input.compare(*i, 4, "log(")) {
    *i += 3;
  } else if (!input.compare(*i, 3, "mod")) {
    *i += 3;
    if (IsOperator(input[*i]))
      throw std::invalid_argument("Неверно составленное выражение! mod\n");
  } else {
    throw std::invalid_argument("Неверно составленное выражение! code:3\n");
  }
}

void s21::SkipBracket(std::string input, int *i, int *bracket) {
  if (input[*i] == '(') {
    (*i)++;
    if (input[*i]) {
      if (input[*i] == ')') {
        throw std::invalid_argument("Неверно используемые скобки!\n");
      } else if (input[*i] == '*' || input[*i] == '/' || input[*i] == '^' ||
                 input[*i] == 'm') {
        throw std::invalid_argument("Неверно составленное выражение! code:2\n");
      } else {
        (*bracket)++;
      }
    } else {
      throw std::invalid_argument("Неверно завершенное выражение!\n");
    }
  } else {
    if (*bracket == 0)
      throw std::invalid_argument("Неверно используемые скобки!!\n");
    (*i)++;
    if (input[*i] == '(' || input[*i] == 'X' || isdigit(input[*i]) ||
        IsFunBegin(input[*i])) {
      throw std::invalid_argument("Неверно составленное выражение!\n");
    } else {
      (*bracket)--;
    }
  }
}

void s21::SkipOperator(std::string input, int *i) {
  (*i)++;
  if (!input[*i] || IsOperator(input[*i]) || input[*i] == 'm')
    throw std::invalid_argument("Неверно составленное выражение! Операторы\n");
}
void s21::CheckInput(std::string input) {
  int len = input.size(), bracket = 0;
  if (input.empty()) {
    throw std::invalid_argument("Введите выражение  для расчета!\n");
  }
  int i = 0;
  if (input[0] == '*' || input[0] == '/' || input[0] == '^' || input[0] == 'm')
    throw std::invalid_argument("Неверно составленное выражение!\n");
  while (i < len) {
    if (isdigit(input[i]) || input[i] == 'X') {
      SkipNumber(input, &i);
    } else if (IsOperator(input[i])) {
      SkipOperator(input, &i);
    } else if (IsBracket(input[i])) {
      SkipBracket(input, &i, &bracket);
    } else if (IsFunBegin(input[i]) || input[i] == 'm') {
      SkipFun(input, &i);
    } else if (input[i] == '.') {
      throw std::invalid_argument("Неверно используемая точка!\n");
    } else {
      throw std::invalid_argument("Наличие невалидных символов!\n");
    }
  }
}

void s21::ErrorXY(std::string input) {
  int dot_readed = 0, dot_caunt = -1, i = 0;
  while (isdigit(input[i]) || (input[i] == '.' && !dot_readed) ||
         (i == 0 && (input[i] == '-' || input[i] == '+'))) {
    if (input[i] == '.') dot_readed = 1;
    if (dot_readed) dot_caunt += 1;
    i += 1;
  }
  if ((dot_readed && input[i] == '.') || dot_caunt > 2)
    throw std::invalid_argument("Введено невалидное число x/y!\n");
  if (input[i])
    throw std::invalid_argument("Наличие невалидных символов в x/y!\n");
}

std::pair<std::vector<double>, std::vector<double>> Model::Graph(
    std::string input, std::string min_x, std::string max_x, std::string min_y,
    std::string max_y) {
  std::pair<std::vector<double>, std::vector<double>> tmp;
  CheckInput(input);
  if (min_x.empty() || max_x.empty() || min_y.empty() || max_y.empty())
    throw std::invalid_argument("Область определения/значения не заполнена!\n");
  double x_1 = SetDouble(min_x);
  double x_2 = SetDouble(max_x);
  double y_1 = SetDouble(min_y);
  double y_2 = SetDouble(max_y);

  if ((x_1 >= x_2) || (y_1 >= y_2))
    throw std::invalid_argument("Область определения/значения не корректна\n");
  double h = (x_2 - x_1) / 1000;
  double res = 0;
  Input_ = input;
  for (double X = x_1; X <= x_2; X += h) {
    X_ = X;
    try {
      res = this->MainCalculation();
      tmp.first.push_back(X);
      tmp.second.push_back(res);
    } catch (std::exception &e) {
    }
  }
  return tmp;
}
