#include "s21_model.h"

using namespace s21;

CreditResult CreditModel::GetResults() {
  CreditResult res;
  res.pay = month_pay_;
  res.perc = percents_;
  res.res_sum = res_sum_;
  return res;
}

double CreditModel::AnnMesP() {
  double mRate = credit_rate_ / 12 / 100, coef = 0;
  coef = (mRate * pow((1 + mRate), credit_time_) /
          (pow(1 + mRate, credit_time_) - 1));
  return coef * credit_sum_;
}

double CreditModel::DiffMesP(double mesPlata, double sum, double rate) {
  return mesPlata + (sum * rate * 30.0 / 365.0);
}

void CreditModel::ResCreditA() {
  month_pay_.first = AnnMesP();
  month_pay_.second = 0;
  res_sum_ = month_pay_.first * credit_time_;
  percents_ = (res_sum_ - credit_sum_);
}

void CreditModel::ResCreditD() {
  res_sum_ = 0;
  double rate = credit_rate_ / 100;
  double sum = credit_sum_;
  double mesPlata = credit_sum_ / credit_time_;
  month_pay_.first = DiffMesP(mesPlata, sum, rate);
  for (int i = 0; i < credit_time_ && sum >= 0; i++) {
    res_sum_ += DiffMesP(mesPlata, sum, rate);
    sum -= mesPlata;
    if (i == credit_time_ - 1) {
      month_pay_.second = DiffMesP(mesPlata, sum, rate);
    }
  }
  percents_ = res_sum_ - credit_sum_;
}

void s21::ErrorNumber(std::string input) {
  int dot_readed = 0, dot_caunt = -1, i = 0;
  while (isdigit(input[i]) || (input[i] == '.' && !dot_readed)) {
    if (input[i] == '.') dot_readed = 1;
    if (dot_readed) dot_caunt += 1;
    i += 1;
  }
  if ((dot_readed && input[i] == '.') || dot_caunt > 2)
    throw std::invalid_argument("Введено невалидное число!\n");
  if (input[i]) throw std::invalid_argument("Наличие невалидных символов!\n");
}

void s21::ErrorData(std::string input) {
  int i = 0;
  while (isdigit(input[i])) {
    i += 1;
  }
  if (input[i]) throw std::out_of_range("Невалидный срок!\n");
}

void CreditModel::CreditCalc(int payType, std::string sum, std::string time,
                             std::string rate) {
  if (!(payType)) throw std::out_of_range("Не выбран режим расчета!");
  if (sum.empty() || time.empty() || rate.empty())
    throw std::invalid_argument("Какая либо из строк пуста!\n");
  ErrorNumber(sum);
  ErrorNumber(rate);
  ErrorNumber(time);
  ErrorData(time);

  // проверка
  credit_sum_ = atof(sum.c_str());
  credit_time_ = atof(time.c_str());
  credit_rate_ = atof(rate.c_str());
  pay_type_ = payType;
  if (pay_type_ == 1) {
    ResCreditA();
  } else {
    ResCreditD();
  }
}