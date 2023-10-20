#include "s21_controller.h"

using namespace s21;

double Controller::Calculate(std::string str, std::string x) {
  Model model;
  return model.Calculator(str, x);
}

std::pair<std::vector<double>, std::vector<double>> Controller::Graph(
    std::string str, std::string x_min, std::string x_max, std::string y_min,
    std::string y_max) {
  Model model;
  return model.Graph(str, x_min, x_max, y_min, y_max);
}

CreditResult Controller::Credit(int pay_type, std::string sum, std::string time,
                                std::string rate) {
  CreditModel creditModel;
  creditModel.CreditCalc(pay_type, sum, time, rate);
  return creditModel.GetResults();
}

DeposResult Controller::Deposit(bool capitalization, int pay_type,
                                std::string sum, std::string time,
                                std::string rate, std::string tax_rate) {
  DepositModel depositModel;
  depositModel.DepositCalc(capitalization, pay_type, sum, time, rate, tax_rate);
  return depositModel.GetResults();
}