#ifndef CONTROLLER_S21_CONTROLLER_H_
#define CONTROLLER_S21_CONTROLLER_H_

#include "../model/s21_model.h"

namespace s21 {

class Controller {
 public:
  Controller() {}
  ~Controller() {}

  double Calculate(std::string str, std::string x);
  std::pair<std::vector<double>, std::vector<double>> Graph(std::string str,
                                                            std::string x_min,
                                                            std::string x_max,
                                                            std::string y_min,
                                                            std::string y_max);
  CreditResult Credit(int pay_type, std::string sum, std::string time,
                      std::string rate);
  DeposResult Deposit(bool capitalization, int pay_type, std::string sum,
                      std::string time, std::string rate, std::string tax_rate);

 private:
};
}  // namespace s21

#endif  //  CONTROLLER_S21_CONTROLLER_H_