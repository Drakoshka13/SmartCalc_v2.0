#include <gtest/gtest.h>

#include "../model/s21_model.h"

#define EPS 1e-7
using namespace s21;

TEST(Calc, Test1) {
  Model s21_model;
  std::string expression = "(2+3)*5^2";
  double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_EQ(result, 125.0);
}

TEST(Calc, Test2) {
  Model s21_model;
  std::string expression = "1/2+(2+3)/(sin(9-2)^2-6/7)";
  double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_NEAR(-11.2505646, result, EPS);
}

TEST(Calc, Test3) {
  Model s21_model;
  std::string expression =
      "sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)";
  long double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_NEAR(-1.4753212, result, EPS);
}

TEST(Calc, Test4) {
  Model s21_model;
  std::string expression = "5*asin(0.11)-(2)*acos(0)";
  long double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_NEAR(-2.59047740365, result, EPS);
}

TEST(Calc, Test5) {
  Model s21_model;
  std::string expression = "-cos(1)/(+52*ln(21))";
  long double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_NEAR(-0.0034128271909763, result, EPS);
}

TEST(Calc, Test6) {
  Model s21_model;
  std::string expression = "3*X-5.5";
  long double result = 0;
  result = s21_model.Calculator(expression, "3");
  EXPECT_NEAR(3.5, result, EPS);
}

TEST(Calc, Test7) {
  Model s21_model;
  std::string expression = "sqrt(+9)";
  double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_EQ(result, 3.0);
}

TEST(Calc, Test8) {
  Model s21_model;
  std::string expression = "123.12";
  double result = 0;
  result = s21_model.Calculator(expression, "0");
  EXPECT_EQ(result, 123.12);
}

TEST(CreditCalc, Test1) {
  CreditModel s21_model;
  s21_model.CreditCalc(1, "20000", "12", "13");
  CreditResult res = s21_model.GetResults();
  EXPECT_NEAR(res.pay.first, 1786.35, 1E-1);
  EXPECT_EQ(res.pay.second, 0);
  EXPECT_NEAR(res.perc, 1436.15, 1E-1);
  EXPECT_NEAR(res.res_sum, 21436.1, 1E-1);
}

TEST(CreditCalc, Test2) {
  CreditModel s21_model;
  s21_model.CreditCalc(2, "20000", "12", "13");
  CreditResult res = s21_model.GetResults();
  EXPECT_NEAR(res.pay.first, 1880.37, 1E-1);
  EXPECT_NEAR(res.pay.second, 1666.67, 1E-1);
  EXPECT_NEAR(res.perc, 1389.04, 1E-1);
  EXPECT_NEAR(res.res_sum, 21389, 1E-1);
}

TEST(DepCalc, Test1) {
  DepositModel s21_model;
  s21_model.DepositCalc(false, 0, "20000", "12", "13", "7.5");
  DeposResult res = s21_model.GetResults();
  EXPECT_NEAR(res.sum, 22600, 1E-1);
  EXPECT_NEAR(res.perc, 2600, 1E-1);
  EXPECT_NEAR(res.tax, 0, 1E-1);
}

TEST(DepCalc, Test2) {
  DepositModel s21_model;
  s21_model.DepositCalc(true, 2, "20000", "12", "13", "7.5");
  DeposResult res = s21_model.GetResults();
  EXPECT_NEAR(res.sum, 22760.65, 1E-1);
  EXPECT_NEAR(res.perc, 2760.65, 1E-1);
  EXPECT_NEAR(res.tax, 0, 1E-1);
}

TEST(DepCalc, Test3) {
  DepositModel s21_model;
  s21_model.DepositCalc(true, 1, "20000", "12", "13", "7.5");
  DeposResult res = s21_model.GetResults();
  EXPECT_NEAR(res.sum, 22776.365, 1E-1);
  EXPECT_NEAR(res.perc, 2776.365, 1E-1);
  EXPECT_NEAR(res.tax, 0, 1E-1);
}

TEST(DepCalc, Test4) {
  DepositModel s21_model;
  s21_model.DepositCalc(true, 3, "1000000", "12", "13", "7.5");
  DeposResult res = s21_model.GetResults();
  EXPECT_NEAR(res.sum, 1128484, 1E-1);
  EXPECT_NEAR(res.perc, 136475.9, 1E-1);
  EXPECT_NEAR(res.tax, 7991.871, 1E-1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
