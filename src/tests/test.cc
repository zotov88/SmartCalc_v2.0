#include <gtest/gtest.h>

#include <string>

#include "../calculator/controller/controller.h"
#include "../calculator/model/model.h"

using namespace s21;

class CalcTest : public ::testing::Test {
 public:
  s21::Calculator calc_model;
  s21::Parser pars_model;
  s21::Validation valid_model;
  s21::Credit credit_model;
  s21::Deposit deposit_model;

  double result = 0;
  double x_value = 0;

};

TEST_F(CalcTest, test_case_1) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "1+2*3/4";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(2.5, result);
}

TEST_F(CalcTest, test_case_2) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-12.3++44--0.123/(60mod21*2.5)";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(31.70273333333333, result);
}

TEST_F(CalcTest, test_case_3) {
  s21::CalcController calc_controller(&calc_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-12.3++44--0.123/(60.mod21*2.5)";
  EXPECT_DOUBLE_EQ(valid_controller.isValid(expression), 0);
}

TEST_F(CalcTest, test_case_4) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "10+2.213";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(12.213, result);
}

TEST_F(CalcTest, test_case_5) {
  s21::CalcController calc_controller(&calc_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "10+2.2.13";
  EXPECT_DOUBLE_EQ(valid_controller.isValid(expression), 0);
}

TEST_F(CalcTest, test_case_6) {
  s21::CalcController calc_controller(&calc_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "sosinus(x)";
  EXPECT_DOUBLE_EQ(valid_controller.isValid(expression), 0);
}

TEST_F(CalcTest, test_case_7) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "10+x";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      x_value = -5.01;
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(4.99, result);
}

TEST_F(CalcTest, test_case_8) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "cos(1)";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0.5403023058681398, result);
}

TEST_F(CalcTest, test_case_9) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-(4.01^sqrt(81))";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-268101.5677574709, result);
}

TEST_F(CalcTest, test_case_10) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-(4.01^-sqrt(81))";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-0.000003729929699272093, result);
}

TEST_F(CalcTest, test_case_11) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-1-1";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-2, result);
}

TEST_F(CalcTest, test_case_12) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-1--1";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0, result);
}

TEST_F(CalcTest, test_case_13) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "1---1";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_14) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "1-1/";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_15) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "*1-1";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_16) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "12.001.1";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_17) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "12,1";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_18) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "()+(45+1)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_19) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(5)+(45+1)";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(51, result);
}

TEST_F(CalcTest, test_case_20) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(3*(6000-(223.12/(2^(1+sqrt(16))))))";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(17979.0825, result);
}

TEST_F(CalcTest, test_case_21) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-(3*(6000-(223.12/(2^(1+sqrt(16))))))";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-17979.0825, result);
}


TEST_F(CalcTest, test_case_22) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(3*(6000-(223.12/(2^(1+sqrt(16))))))*0";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0, result);
}

TEST_F(CalcTest, test_case_23) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(3*(6000-((223.12/(2^(1+sqrt(16))))))";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0, result);
}

TEST_F(CalcTest, test_case_24) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "acos(1)";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0, result);
}

TEST_F(CalcTest, test_case_25) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-sin(cos(tan(sqrt(6mod2*(-2-4)))))";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-0.8414709848078965, result);
}

TEST_F(CalcTest, test_case_26) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "3^3";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(27, result);
}

TEST_F(CalcTest, test_case_27) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "3^-3";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0.037037037037037035, result);
}

TEST_F(CalcTest, test_case_28) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-3^3";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-27, result);
}

TEST_F(CalcTest, test_case_29) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-3^-3";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-0.0370370370370370355, result);
}

TEST_F(CalcTest, test_case_30) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-(-3^-3)";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(0.037037037037037035, result);
}

TEST_F(CalcTest, test_case_31) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "6/2*(1+2)";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(9, result);
}

TEST_F(CalcTest, test_case_32) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "1111111111111111111111111+1111111111111111111111111";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(2.2222222222222222e+24, result);
}

TEST_F(CalcTest, test_case_33) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "sin(x)";
  EXPECT_DOUBLE_EQ(1, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_34) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_35) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "1x";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_36) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "1+2(3)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_37) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "3-xsin(3)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_38) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "x";
  EXPECT_DOUBLE_EQ(1, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_39) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "123";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(123, result);
}

TEST_F(CalcTest, test_case_40) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-123.123";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-123.123, result);
}

TEST_F(CalcTest, test_case_41) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "xx";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_42) {
  s21::CalcController calc_controller(&calc_model);
  s21::ParserController pars_controller(&pars_model);
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "2-(x+x)-10*x";
  if (valid_controller.isValid(expression)) {
      char* rpn = pars_controller.parsing(expression);
      x_value = 4;
      result = calc_controller.calculation(rpn, x_value);
      free(rpn);
  }
  EXPECT_DOUBLE_EQ(-46, result);
}

TEST_F(CalcTest, test_case_43) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "3*-xsin(3)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_44) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "3-/xsin(x)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_45) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "--";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_46) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(-)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_47) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "3^x";
  EXPECT_DOUBLE_EQ(1, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_48) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(12mod^2)";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_49) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(-12(1))";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_50) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(11)3";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_51) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "(11)x";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_52) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "-1-";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_53) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "x1";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_54) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "cos(x)1";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_55) {
  s21::ValidationController valid_controller(&valid_model);
  const char* expression = "cos(1)x";
  EXPECT_DOUBLE_EQ(0, valid_controller.isValid(expression));
}

TEST_F(CalcTest, test_case_56) {
  s21::CreditController cred_controller(&credit_model);
  s21::Credit::DataCred data;
  cred_controller.creditCalc(300000, 24, 20, 1, &data);
  int overpay = data.overpayment;
  int pay = data.payment;
  int total_pay = data.total_payment;
  EXPECT_DOUBLE_EQ(66449, overpay);
  EXPECT_DOUBLE_EQ(15268, pay);
  EXPECT_DOUBLE_EQ(366449, total_pay);
}

TEST_F(CalcTest, test_case_57) {
  s21::CreditController cred_controller(&credit_model);
  s21::Credit::DataCred data;
  cred_controller.creditCalc(300000, 24, 20, 2, &data);
  int overpay = data.overpayment;
  int first_pay = data.first_payment;
  int last_pay = data.last_payment;
  int total_pay = data.total_payment;
  EXPECT_DOUBLE_EQ(62500, overpay);
  EXPECT_DOUBLE_EQ(17500, first_pay);
  EXPECT_DOUBLE_EQ(12708, last_pay);
  EXPECT_DOUBLE_EQ(362500, total_pay);
}

TEST_F(CalcTest, test_case_58) {
  s21::DepositController dep_controller(&deposit_model);
  s21::Deposit::DataDep data;
  dep_controller.depositCalc(100000, 12, 20, 7, (char *)"ежемесячно", (char *)"в конце", (char *)"нет", 4, 5, &data);
  int percent = data.percent;
  int dep_end = data.deposit_end;
  int tax = data.tax;
  EXPECT_DOUBLE_EQ(21939, percent);
  EXPECT_DOUBLE_EQ(121939, dep_end);
  EXPECT_DOUBLE_EQ(0, tax);
}

TEST_F(CalcTest, test_case_59) {
  s21::DepositController dep_controller(&deposit_model);
  s21::Deposit::DataDep data;
  dep_controller.depositCalc(200000, 10, 25, 7.5, (char *)"ежемесячно", (char *)"в конце", (char *)"ежемесячно", 11, 1000, &data);
  int percent = data.percent;
  int dep_end = data.deposit_end;
  int tax = data.tax;
  EXPECT_DOUBLE_EQ(57018, percent);
  EXPECT_DOUBLE_EQ(257018, dep_end);
  EXPECT_DOUBLE_EQ(0, tax);
}

TEST_F(CalcTest, test_case_60) {
  s21::DepositController dep_controller(&deposit_model);
  s21::Deposit::DataDep data;
  dep_controller.depositCalc(300000, 18, 5, 7, (char *)"нет", (char *)"ежемесячно", (char *)"ежемесячно", 13, 1500, &data);
  int percent = data.percent;
  int dep_end = data.deposit_end;
  int tax = data.tax;
  EXPECT_DOUBLE_EQ(23456, percent);
  EXPECT_DOUBLE_EQ(348956, dep_end);
  EXPECT_DOUBLE_EQ(0, tax);
}

TEST_F(CalcTest, test_case_61) {
  s21::DepositController dep_controller(&deposit_model);
  s21::Deposit::DataDep data;
  dep_controller.depositCalc(300000, 18, 15, 7, (char *)"нет", (char *)"ежемесячно", (char *)"нет", 8, 0, &data);
  int percent = data.percent;
  int dep_end = data.deposit_end;
  int tax = data.tax;
  EXPECT_DOUBLE_EQ(64620, percent);
  EXPECT_DOUBLE_EQ(364620, dep_end);
  EXPECT_DOUBLE_EQ(2880, tax);
}

TEST_F(CalcTest, test_case_62) {
  s21::DepositController dep_controller(&deposit_model);
  s21::Deposit::DataDep data;
  dep_controller.depositCalc(300000, 18, 15, 7, (char *)"6 месяцев", (char *)"3 месяца", (char *)"1 год", 8, 0, &data);
  int percent = data.percent;
  int dep_end = data.deposit_end;
  int tax = data.tax;
  EXPECT_DOUBLE_EQ(72689, percent);
  EXPECT_DOUBLE_EQ(372689, dep_end);
  EXPECT_DOUBLE_EQ(0, tax);
}

TEST_F(CalcTest, test_case_63) {
  s21::DepositController dep_controller(&deposit_model);
  s21::Deposit::DataDep data;
  dep_controller.depositCalc(300000, 18, 15, 7, (char *)"нет", (char *)"нет", (char *)"3 месяца", 8, 0, &data);
  int percent = data.percent;
  int dep_end = data.deposit_end;
  int tax = data.tax;
  EXPECT_DOUBLE_EQ(64620, percent);
  EXPECT_DOUBLE_EQ(364620, dep_end);
  EXPECT_DOUBLE_EQ(2880, tax);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
