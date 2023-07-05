#include "controller.h"

using namespace s21;

double CalcController::calculation(const char* rpn, double x) {
  return calc_model->calculation(rpn, x);
}

char* ParserController::parsing(const char* expression) {
  return p_model->parsing(expression);
}

int ValidationController::isValid(const char* str) {
  return v_model->isValid(str);
}

void CreditController::creditCalc(double sum, int month, double rate, int type,
                                  Credit::DataCred* data) {
  c_model->creditCalc(sum, month, rate, type, data);
}

void DepositController::depositCalc(double deposit_start, int period,
                                    double rate, double key_rate, char* capital,
                                    char* payout, char* replenishment,
                                    double tax_type, double replenish,
                                    Deposit::DataDep* data) {
  d_model->depositCalc(deposit_start, period, rate, key_rate, capital, payout,
                       replenishment, tax_type, replenish, data);
}
