#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <cstring>
#include <list>
#include <stack>
#include <string>

#define UNAR_OP "sctSCTlLq"
#define BINAR_OP "-+/*^m"
#define MONTH 30.4167
#define WORD "нет"

namespace s21 {

/**
 @brief Класс для осуществления валидации принимаемого выражения
*/
class Validation {
 public:
  Validation() {}

  /**
   @brief Главная функция определения валидности выражения
   @details В функции агрегируются все посимвольные проверки. Если они успешно
   завершаются, проверяется валидность расстановки скобок
   @param str строка с выражением
   @return 1/0 в случае допустимого/не допустимого выражения
  */
  int isValid(const char *str);

  /**
   @brief Функция проверки операторов +*-/
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isOperator(char c);

  /**
   @brief Функция проверки унарных операторов +-
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isUnar(char c);

  /**
   @brief Функция проверки цифры
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isDigit(char c);

  /**
   @brief Функция проверки x
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isX(char c);

  /**
   @brief Функция проверки оператора возведения в степень
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isPow(char c);

  /**
   @brief Функция проверки открывающейся скобки
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isLBracket(char c);

  /**
   @brief Функция проверки закрывающейся скобки
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isRBracket(char c);

  /**
   @brief Функция проверки точки
   @param c символ из строки
   @return 1/0 в случае успеха/неудачи
  */
  int isPoint(int c);

  /**
   @brief Функция проверки оператора остатка от деления
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int isMod(const char *str, int index);

  /**
   @brief Функция проверки первой буквы фнкуции
   @param c выражение
   @return 1/0 в случае успеха/неудачи
  */
  int isFirstLetFunc(char c);

  /**
   @brief Функция сверяет полученный отрезок из строки с массивом функций
   @param str выражение
   @param index индекс строки
   @param func указатель на хранилище для полученной функции из выражения
   @return указатель на хранилище для полученной функции
  */
  char *subFu(const char *str, int index, char *func);

  /**
   @brief Функция проверки валидности унарных +/-
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkUnar(const char *str, int index);

 private:
  /**
   @brief Функция проверки правильности расположения скобок
   @param str строка с выражением
   @return 1/0 в случае успеха/неудачи
  */
  int isBraketsValid(const char *str);

  /**
   @brief Функция проверки оставшихся скобок в выражении
   @details Алгоритм проверки валидности скобок предполагает проверку на наличие
   оставшихся скобок в выражении, если цикл прервался
   @param str строка с выражением
   @return 1/0 в случае успеха/неудачи
  */
  int isNoMoreBrakets(const char *str);

  /**
   @brief Функция проверки наличия "пустых" скобок
   @param str строка с выражением
   @return 1/0 в случае успеха/неудачи
  */
  int isBraketsNotEmpty(const char *str);

  /**
   @brief Функция проверки функции (sin, cos ...)
   @param str выражение
   @param index индекс строки
   @param func указатель на хранилище для полученной функции из выражения
   @return 1/0 в случае успеха/неудачи
  */
  int isFunc(const char *str, int index, char *func);

  /**
   @brief Функция проверки валидности цифры
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkDigit(const char *str, int index);

  /**
   @brief Функция проверки валидности 'x'
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkX(const char *str, int index);

  /**
   @brief Функция проверки валидности оператора
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkOperator(const char *str, int index);

  /**
   @brief Функция проверки валидности точки
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkPoint(const char *str, int index);

  /**
   @brief Функция проверки валидности оператора mod
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkMod(const char *str, int index);

  /**
   @brief Функция проверки валидности возведения степени
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkPow(const char *str, int index);

  /**
   @brief Функция проверки валидности открывающейся скобки
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkLBraket(const char *str, int index);

  /**
   @brief Функция проверки валидности закрывающейся скобки
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkRBraket(const char *str, int index);

  /**
   @brief Функция проверки валидности названия функции
   @param str выражение
   @param start индекс первого символа функии в строке
   @param end индекс последнего символа функии в строке
   @return 1/0 в случае успеха/неудачи
  */
  int chekFunc(const char *str, int start, int end);

  /**
   @brief Функция проверки операторов справа и слева от унарных +/-
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int checkOperatorsLandR(const char *str, int index);

  /**
   @brief Функция проверки наличия еще одной точки в числе
   @param str выражение
   @param index индекс строки
   @return 1/0 в случае успеха/неудачи
  */
  int isPointExist(const char *str, int index);
};

/**
 @brief Класс для осуществления подсчета выражения в обратной польской нотации
*/
class Calculator {
 public:
  Calculator() {}

  /**
   @brief Функия подсчета распарсенного выражения
   @param rpn выражение в польской нотации
   @param x значение x
   @return результат выражения
  */
  double calculation(const char *rpn, double x);

 private:
  Validation *v;

  /**
   @brief Функия для конвертации строки из массива чаров в double
   @param rpn выражение в польской нотации
   @return сконвертированное число
  */
  double getDigit(const char **rpn);

  /**
   @brief Функия для определения унарного минуса в строке
   @param c символ из строки
   @return 1/0 в случае успеха/не успеха
  */
  int isUnarMinus(char c);

  /**
   @brief Функия для определения бинарного оператора ("-+/^m*")
   @param c символ из строки
   @return 1/0 в случае успеха/не успеха
  */
  int isBinarOperator(char c);

  /**
   @brief Функия для определения унарного оператора ("cos, sin ...")
   @param c символ из строки
   @return 1/0 в случае успеха/не успеха
  */
  int isUnarOperator(char c);

  /**
   @brief Функия подсчета выражения с участием бинарного оператора
   @param c символ из строки
   @return стек
  */
  std::stack<double> binarCalc(char c, std::stack<double> stack);

  /**
   @brief Функия подсчета выражения с участием унарного оператора
   @param c символ из строки
   @param stack стек для хранения числовых значений
   @return стек
  */
  std::stack<double> unarCalc(char c, std::stack<double> stack);
};

/**
 @brief Класс для осуществления парсинга принимаемого выражения в обратную
 польскую нотацию
*/
class Parser {
 public:
  Parser() {}

  /**
   @brief Функия парсинга выражения в обратную польскую нотацию
   @param expression проверенное на валидность выражение
   @details внутри функции выделяется динамическая память под указатель чаров,
   он же и возвращается. Соответственно полученный указатель нужно очищать.
   @return указатель на выражение в обратной польской нотации
  */
  char *parsing(const char *expression);

 private:
  Validation *v;

  /**
   @brief Функия удаления лишних пробелов в обратной польской нотации
   @param rpn обратная польская нотация
  */
  void deleteExtraSpases(char *rpn);

  /**
   @brief Функия определения буквы функции, помещаемой в польскую нотацию
   @param function указатель на начало функции в выражении
   @return символ, определяющий функцию в обратной польской нотации
  */
  char getLetFun(char *function);

  /**
   @brief Функия определения приоритета между операторами
   @param inExp символ из выражения
   @param inSt символ из стека
   @return 1 в случае, если опертор из выражения имеет меньший или равный
   приоритет в сравнении с опреатором из стека. 0 в противном случае
  */
  int checkPriority(char inExp, char inSt);

  /**
   @brief Функия определения приоритета оператора
   @param c оператор
   @return значение приоритета
  */
  int getPriority(char c);
};

/**
 @brief Класс для осуществления вычисления параметров по кредиту
*/
class Credit {
 public:
  Credit() {}

  /**
   @brief Структура для хранения данных, необходимых для кредитного калькулятора
  */
  struct DataCred {
    double payment, overpayment, total_payment, first_payment, last_payment;
  };

  /**
   @brief Функция для вычисления данных о кредите
   @param sum сумма кредита
   @param month срок кредита
   @param rate процентная ставка по кредиту
   @param type тип кредита (1 - аннуитетный, 2 - дифференциированный)
   @param data структура для хранения данных
  */
  void creditCalc(double sum, int month, double rate, int type, DataCred *data);

 private:
  /**
   @brief Функция, вычисляющая аннуитетные платежи
   @param sum сумма кредита
   @param month срок кредита
   @param rate процентная ставка по кредиту
   @param data структура для хранения данных
  */
  void anuitet(double sum, int month, double rate, DataCred *data);

  /**
   @brief Функция, вычисляющая дифференцированные платежи
   @param sum сумма кредита
   @param month срок кредита
   @param rate процентная ставка по кредиту
   @param data структура для хранения данных
  */
  void different(double sum, int month, double rate, DataCred *data);
};

/**
 @brief Класс для осуществления вычисления параметров по вкладу
*/
class Deposit {
 public:
  Deposit() {}

  /**
   @brief Структура для хранения данных, необходимых для депозитного
   калькулятора
  */
  struct DataDep {
    int period;
    double deposit_start, deposit_end, rate, key_rate, tax_type, replenish,
        percent, tax;
    char *payout, *replenishment, *capital;
  };

  /**
   @brief Функция для вычисления данных о депозите
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
                   double key_rate, char *capital, char *payout,
                   char *replenishment, double tax_type, double replenish,
                   DataDep *data);

 private:
  /**
   @brief Функция, подсчитывающая проценты с капитализацией
   @param data структура для хранения данных, необходимых для депозитного
   калькулятора
  */
  void withCapitalisation(DataDep *data);

  /**
   @brief Функция, подсчитывающая проценты без капитализации
   @param data структура для хранения данных, необходимых для депозитного
   калькулятора
  */
  void withoutCapitalisation(struct DataDep *data);

  /**
   @brief Функция, подсчитывающая уплаченные налоги
   @param data структура для хранения данных, необходимых для депозитного
   калькулятора
  */
  void calculateTax(DataDep *data);

  /**
   @brief Функция, подсчитывающая проценты с периодичными пополгнениями без
   капитализации
   @param data структура для хранения данных, необходимых для депозитного
   калькулятора
  */
  void calcReplWithoutCapitalisation(DataDep *data);

  /**
   @brief Функция, определяющая периодичность события
   @param str статус события в виде строки
   @return периодичность события в числовом виде
  */
  int getStatus(char *str);

  /**
   @brief Функция, подсчитывающая процет по вкладу
   @param str статус события в виде строки
   @return периодичность события в числовом виде
  */
  double calculatePercent(int deposit_start, double rate, int period);
};

enum { FAILURE, SUCCESS };

}  // namespace s21

#endif  // MODEL_H
