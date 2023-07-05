#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/model.h"

namespace s21 {

class MainWindow;

/**
 @brief Контроллер для работы с моделью калькуляции
*/
class CalcController {
 private:
  Calculator* calc_model;

 public:
  explicit CalcController(Calculator* m) : calc_model(m) {}

  /**
   @brief Функция, вызывающая модель для осуществления подсчета выражения
   @param rpn выражение в обратной польской нотации
   @param x значение x
   @return результат вычисления
  */
  double calculation(const char* rpn, double x);
};

/**
 @brief Контроллер для работы с моделью парсинга выражения
*/
class ParserController {
 private:
  Parser* p_model;

 public:
  explicit ParserController(Parser* p) : p_model(p) {}

  /**
   @brief Функция, вызывающая модель для осуществления парсинга выражения
   @param expression полученное от пользователя выражение
   @return выражение в обратной польской нотации
  */
  char* parsing(const char* expression);
};

/**
 @brief Контроллер для работы с моделью валидации выражения
*/
class ValidationController {
 private:
  Validation* v_model;

 public:
  explicit ValidationController(Validation* v) : v_model(v) {}

  /**
   @brief Функция, вызывающая модель для осуществления валидации выражения
   @param str полученное от пользователя выражение
   @return 1 или 0 валидное/не валидное выражение
  */
  int isValid(const char* str);
};

/**
 @brief Контроллер для работы с моделью кредитного калькулятора
*/
class CreditController {
 private:
  Credit* c_model;

 public:
  explicit CreditController(Credit* c) : c_model(c) {}

  /**
   @brief Функция, вызывающая модель для вычисления данных о кредите
   @param sum сумма кредита
   @param month срок кредита
   @param rate процентная ставка по кредиту
   @param type тип кредита (1 - аннуитетный, 2 - дифференциированный)
   @param data структура для хранения данных
  */
  void creditCalc(double sum, int month, double rate, int type,
                  Credit::DataCred* data);
};

/**
 @brief Контроллер для работы с моделью депозитного калькулятора
*/
class DepositController {
 private:
  Deposit* d_model;

 public:
  explicit DepositController(Deposit* d) : d_model(d) {}

  /**
   @brief Функция, вызывающая модель для вычисления данных о депозите
   @param deposit_start сумма вклада в начале срока
   @param period срок депозита
   @param rate ставка по вкладу
   @param key_rate ключевая ставка
   @param capital параметр капитализации вклада
   @param payout периодичность выплат
   @param replenishment периодичность пополнения
   @param tax_type налоговая ставка
   @param replenish сумма пополнения
   @param data структура для хранения данных, необходимых для депозитного
   калькулятора
  */
  void depositCalc(double deposit_start, int period, double rate,
                   double key_rate, char* capital, char* payout,
                   char* replenishment, double tax_type, double replenish,
                   Deposit::DataDep* data);
};

}  // namespace s21

#endif  // CONTROLLER_H_
