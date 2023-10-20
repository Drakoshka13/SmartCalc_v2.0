#include "s21_model.h"

using namespace s21;

DeposResult DepositModel::GetResults() {
  DeposResult res;
  res.sum = res_sum_;
  res.perc = profit_;
  res.tax = tax_sum_;
  return res;
}

void DepositModel::DepositCalc(bool capitalization, int pay_period,
                               std::string sum, std::string time,
                               std::string rate, std::string tax_rate) {
  if ((capitalization) && !(pay_period))
    throw std::out_of_range("Не выбрана периодичность выплат!");
  if (sum.empty() || time.empty() || rate.empty() || tax_rate.empty())
    throw std::invalid_argument("Какая либо из строк пуста!\n");

  ErrorNumber(sum);
  ErrorNumber(rate);
  ErrorNumber(tax_rate);
  ErrorNumber(time);
  ErrorData(time);

  dep_sum_ = atof(sum.c_str());
  dep_time_ = atof(time.c_str());
  dep_rate_ = atof(rate.c_str());
  dep_tax_rate_ = atof(tax_rate.c_str());
  payment_period_ = pay_period;
  capitalization_ = capitalization;
  ResDeposit();
}

void DepositModel::ResDeposit() {
  if (capitalization_) {
    switch (payment_period_) {
      case 1:
        res_sum_ = dep_sum_ * pow(1 + dep_rate_ / 100 / 365, dep_time_ * 30.42);
        break;
      case 2:
        res_sum_ = dep_sum_ * pow(1 + dep_rate_ / 100 / 12, dep_time_);
        break;
      case 3:
        res_sum_ = dep_sum_ * pow(1 + dep_rate_ / 100 / 4, dep_time_ / 3);
        break;
      default:
        break;
    }
    profit_ = res_sum_ - dep_sum_;
  } else {
    profit_ = (dep_sum_ * dep_rate_ * dep_time_ / 12) / 100;
    res_sum_ = dep_sum_ + profit_;
  }
  double no_tax_sum;
  no_tax_sum = 1000000 * dep_tax_rate_ / 100;
  if (profit_ > no_tax_sum) {
    tax_sum_ = 0.13 * (profit_ - no_tax_sum * ceil(dep_time_ / 12));
    res_sum_ = res_sum_ - tax_sum_;
  } else {
    tax_sum_ = 0;
  }
}
