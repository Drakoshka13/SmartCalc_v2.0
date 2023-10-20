#ifndef MODEL_S21_MODEL_H_
#define MODEL_S21_MODEL_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

typedef enum {  // google style!
  S21_PLUS = 1,
  S21_MINUS = 2,
  S21_DIV = 3,
  S21_MUL = 4,
  S21_POW = 5,
  S21_MOD = 6,
  S21_COS = 7,
  S21_SIN = 8,
  S21_TAN = 9,
  S21_ACOS = 10,
  S21_ASIN = 11,
  S21_ATAN = 12,
  S21_SQRT = 13,
  S21_LN = 14,
  S21_LOG = 15,
  S21_LEFT_SCOBE = 16,
  S21_RIGHT_SCOBE = 17,
  S21_X = 18,
  S21_UN_PLUS = 19,
  S21_UN_MINUS = 20,
  S21_NUMBER = 21
} s21_lexeme;

namespace s21 {

typedef struct credit_result {
  std::pair<double, double> pay;
  double perc;
  double res_sum;
} CreditResult;

typedef struct deposit_result {
  double sum;
  double perc;
  double tax;
} DeposResult;

void ErrorNumber(std::string input);
void ErrorData(std::string input);
bool IsOperator(char sym);
bool IsBracket(char sym);
bool IsFunBegin(char sym);
void SkipNumber(std::string input, int *i);
void SkipFun(std::string input, int *i);
void SkipBracket(std::string input, int *i, int *bracket);
void SkipOperator(std::string input, int *i);
void CheckInput(std::string input);
void ErrorXY(std::string input);

class Model {
 public:
  Model(){};
  ~Model(){};

  double Calculator(std::string input, std::string x);
  std::pair<std::vector<double>, std::vector<double>> Graph(std::string input,
                                                            std::string min_x,
                                                            std::string max_x,
                                                            std::string min_y,
                                                            std::string max_y);

  void SetInput(std::string input);
  void SetX(std::string x);

 private:
  typedef struct Lexeme {
    double value;
    s21_lexeme type;
    int priority;
  } Lexeme;

  double X_;
  double result_;
  std::string Input_;
  std::vector<Lexeme> Postfix_;
  std::vector<Lexeme> Infix_;

  double MainCalculation();
  void PolTransform();
  void PolCalc();
  Lexeme CheckLexeme(int *i, int *unar);
  void StringToLexeme();
  double UnaryOperation(double a, s21_lexeme op);
  double BinaryOperation(double a, double b, s21_lexeme op);
  double SetDouble(std::string x);
};

class CreditModel {
 public:
  CreditModel(){};
  ~CreditModel(){};

  void CreditCalc(int payType, std::string sum, std::string time,
                  std::string rate);
  CreditResult GetResults();

 private:
  double credit_sum_;
  int credit_time_;
  double credit_rate_;
  int pay_type_;
  std::pair<double, double> month_pay_;
  double percents_;
  double res_sum_;

  double AnnMesP();
  double DiffMesP(double mesPlata, double sum, double rate);
  void ResCreditA();
  void ResCreditD();
};

class DepositModel {
 public:
  DepositModel(){};
  ~DepositModel(){};

  void DepositCalc(bool capitalization, int payType, std::string sum,
                   std::string time, std::string rate, std::string tax_rate);
  DeposResult GetResults();

 private:
  double dep_sum_;
  int dep_time_;
  double dep_rate_;
  double dep_tax_rate_;
  int payment_period_;
  bool capitalization_;
  double res_sum_;
  double profit_;
  double tax_sum_;

  void ResDeposit();
};

}  // namespace s21

#endif  //  MODEL_S21_MODEL_H_