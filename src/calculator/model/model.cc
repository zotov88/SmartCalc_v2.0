#include "model.h"

using namespace s21;

double Calculator::calculation(const char *rpn, double x) {
  std::stack<double> stack;
  char c;
  while ((c = *rpn) != '\0') {
    if (v->isDigit(c)) stack.push(getDigit(&rpn));
    if (v->isX(c)) stack.push(x);
    if (isUnarMinus(c)) stack.top() *= -1;
    if (isBinarOperator(c)) stack = binarCalc(*rpn, stack);
    if (isUnarOperator(c)) stack = unarCalc(*rpn, stack);
    rpn++;
  }
  double result = stack.top();
  stack.pop();
  return result;
}

double Calculator::getDigit(const char **rpn) {
  char num[300] = {0};
  size_t len = strspn(*(rpn), "0123456789.");
  strncpy(num, *(rpn), len);
  *(rpn) += len;
  return atof(num);
}

int Calculator::isUnarMinus(char c) { return c == '~'; }

std::stack<double> Calculator::binarCalc(char c, std::stack<double> stack) {
  double d2 = stack.top();
  stack.pop();
  double d1;
  if (stack.empty()) {
    d1 = 0;
  } else {
    d1 = stack.top();
    stack.pop();
  }
  if (c == '+') stack.push(d1 + d2);
  if (c == '-') stack.push(d1 - d2);
  if (c == '*') stack.push(d1 * d2);
  if (c == '/') stack.push(d1 / d2);
  if (c == '^') stack.push(pow(d1, d2));
  if (c == 'm') stack.push(fmod(d1, d2));
  return stack;
}

std::stack<double> Calculator::unarCalc(char c, std::stack<double> stack) {
  double d = stack.top();
  stack.pop();
  if (c == 's') stack.push(sin(d));
  if (c == 'c') stack.push(cos(d));
  if (c == 't') stack.push(tan(d));
  if (c == 'S') stack.push(asin(d));
  if (c == 'C') stack.push(acos(d));
  if (c == 'T') stack.push(atan(d));
  if (c == 'l') stack.push(log(d));
  if (c == 'L') stack.push(log10(d));
  if (c == 'q') stack.push(sqrt(d));
  return stack;
}

int Calculator::isBinarOperator(char c) {
  return strchr(BINAR_OP, c) == NULL ? FAILURE : SUCCESS;
}

int Calculator::isUnarOperator(char c) {
  return strchr(UNAR_OP, c) == NULL ? FAILURE : SUCCESS;
}

int Validation::isValid(const char *str) {
  int status = 0;
  char c;
  int index = 0;
  while ((c = str[index]) != '\0') {
    status = 0;
    status += isDigit(c) && checkDigit(str, index);
    status += isX(c) && checkX(str, index);
    status += isOperator(c) && checkOperator(str, index);
    status += isUnar(c) && checkUnar(str, index);
    status += isLBracket(c) && checkLBraket(str, index);
    status += isRBracket(c) && checkRBraket(str, index);
    status += isPow(c) && checkPow(str, index);
    status += isPoint(c) && checkPoint(str, index);
    if (isMod(str, index) && checkMod(str, index)) {
      status++;
      index += 2;
    }
    char fun[5] = "";
    if (isFunc(str, index, fun) && chekFunc(str, index, index + strlen(fun))) {
      status++;
      index += strlen(fun) - 1;
    }
    index++;
    if (!status) break;
  }
  return isBraketsValid(str) && isBraketsNotEmpty(str) ? status : 0;
}

int Validation::isBraketsValid(const char *str) {
  std::stack<char> stack;
  int result = FAILURE;
  char c;
  while ((c = *str) != '\0') {
    if (c == '(') {
      stack.push(')');
    }
    if (c == ')' && (stack.empty() || stack.top() != c)) {
      stack.pop();
      break;
    }
    if (c == ')') {
      stack.pop();
    }
    str++;
  }
  if (isNoMoreBrakets(str) && stack.empty()) {
    result = SUCCESS;
  }
  return result;
}

int Validation::isNoMoreBrakets(const char *str) {
  return strchr(str, ')') == NULL && strchr(str, '(') == NULL;
}

int Validation::isBraketsNotEmpty(const char *str) {
  return strstr(str, "()") == NULL;
}

int Validation::isDigit(char c) { return c >= '0' && c <= '9'; }

int Validation::isX(char c) { return c == 'x'; }

int Validation::isOperator(char c) { return strchr("+-*/", c) == NULL ? 0 : 1; }

int Validation::isUnar(char c) { return c == '+' || c == '-'; }

int Validation::isPow(char c) { return c == '^'; }

int Validation::isLBracket(char c) { return c == '('; }

int Validation::isRBracket(char c) { return c == ')'; }

int Validation::isPoint(int c) { return c == '.'; }

int Validation::isMod(const char *str, int index) {
  int result = -1;
  if (index >= 0 && index < (int)strlen(str)) {
    result = strncmp("mod", str + index, 3);
  }
  return result == 0 ? 1 : 0;
}

int Validation::isFunc(const char *str, int index, char *func) {
  subFu(str, index, func);
  return strcmp(func, "") != 0;
}

char *Validation::subFu(const char *str, int index, char *func) {
  const char *functions[9] = {"sqrt", "cos",  "sin", "tan", "acos",
                              "asin", "atan", "ln",  "log"};
  for (int i = 0; i < 9; i++) {
    const char *stmp = str + index;
    if (strspn(functions[i], stmp) == strlen(functions[i]) &&
        !strncmp(stmp, functions[i], strlen(functions[i]))) {
      strcpy(func, functions[i]);
      break;
    }
  }
  return func;
}

int Validation::checkDigit(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0) {
    char l = str[index - 1];
    left = isDigit(l) + (isOperator(l) || isUnar(l)) + isLBracket(l) +
           isPow(l) + isPoint(l) + isMod(str, index - 3) - isX(l);
  }
  if (index != length - 1) {
    char r = str[index + 1];
    right = isDigit(r) + isOperator(r) + isRBracket(r) + isPow(r) + isPoint(r) +
            isMod(str, index + 1) - isLBracket(r) - isX(r) - isFirstLetFunc(r);
  }
  return left + right > 0 || length == 1;
}

int Validation::checkX(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0) {
    char l = str[index - 1];
    left = (isOperator(l) || isUnar(l)) + isLBracket(l) + isPow(l) +
           isMod(str, index - 3);
  }
  if (index != length - 1) {
    char r = str[index + 1];
    right = isOperator(r) + isRBracket(r) + isPow(r) + isMod(str, index + 1) -
            isLBracket(r) - isX(r) - isFirstLetFunc(r);
  }
  return left + right > 0 || length == 1;
}

int Validation::checkOperator(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0) {
    char l = str[index - 1];
    left = isDigit(l) + isX(l) + isRBracket(l);
  }
  if (index != length - 1) {
    char r = str[index + 1];
    right = isDigit(r) + isX(r) + isLBracket(r) + isFirstLetFunc(r) + isUnar(r);
  }
  return left + right == 2;
}

int Validation::checkPoint(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0 && index != length - 1) {
    char l = str[index - 1];
    char r = str[index + 1];
    left = isDigit(l);
    right = isDigit(r);
  }
  int result = left + right;
  result = isPointExist(str, index + 1) ? 0 : result;
  return result == 2;
}

int Validation::checkMod(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0) {
    char l = str[index - 1];
    left = isDigit(l) + isX(l) + isRBracket(l);
  }
  if (index + 2 != length - 1) {
    char r = str[index + 3];
    right = isDigit(r) + isX(r) + isLBracket(r) + isFirstLetFunc(r) + isUnar(r);
  }
  return left + right == 2;
}

int Validation::checkPow(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0 && index != length - 1) {
    char l = str[index - 1];
    char r = str[index + 1];
    left = isDigit(l) + isX(l) + isRBracket(l);
    right = isDigit(r) + isX(r) + isLBracket(r) + isFirstLetFunc(r) + isUnar(r);
  }
  return left + right == 2;
}

int Validation::checkLBraket(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0 && index != length - 1) {
    char l = str[index - 1];
    left = isOperator(l) + isLBracket(l) + isPow(l) + isMod(str, index - 3) -
           isRBracket(l);
  }
  if (index != length - 1) {
    char r = str[index + 1];
    right = isDigit(r) + isX(r) + isLBracket(r) + isFirstLetFunc(r) + isUnar(r);
  }
  return left + right > 0;
}

int Validation::checkRBraket(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0) {
    char l = str[index - 1];
    left = isDigit(l) + isX(l) + isRBracket(l);
  }
  if (index != length - 1 && index != 0) {
    char r = str[index + 1];
    right = isOperator(r) + isRBracket(r) + isPow(r) + isMod(str, index + 1) -
            isLBracket(r);
  }
  return left + right > 0;
}

int Validation::checkUnar(const char *str, int index) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (index != 0) {
    int l = str[index - 1];
    left = isOperator(l) + isLBracket(l) + isMod(str, index - 3) - isDigit(l) -
           isX(l) - isRBracket(l);
  }
  if (index != length - 1) {
    int r = str[index + 1];
    right = isDigit(r) + isX(r) + isLBracket(r) + isFirstLetFunc(r) + isPow(r);
  }
  int result = left + right;
  result = checkOperatorsLandR(str, index) ? result : 0;
  return result > 0;
}

int Validation::chekFunc(const char *str, int start, int end) {
  int left = 0;
  int right = 0;
  int length = strlen(str);
  if (start != 0) {
    char l = str[start - 1];
    left = isOperator(l) + isPow(l) + isLBracket(l) + isMod(str, start - 3);
  }
  if (end != length - 1) {
    char r = str[end];
    right = isLBracket(r);
  }
  return left + right > 0;
}

int Validation::checkOperatorsLandR(const char *str, int index) {
  int result = SUCCESS;
  if (index - 1 >= 0 && index + 1 < (int)strlen(str)) {
    if ((isOperator(str[index - 1]) && isOperator(str[index - 2])) ||
        isOperator(str[index + 1])) {
      result = FAILURE;
    }
  }
  return result;
}

int Validation::isPointExist(const char *str, int index) {
  int result = FAILURE;
  if (index < (int)strlen(str)) {
    while (isDigit(str[index]) && str[index] != '\0') {
      index++;
    }
    result = (str[index] != '\0') ? isPoint(str[index]) : FAILURE;
  }
  return result;
}

int Validation::isFirstLetFunc(char c) {
  return strchr("cstal", c) == NULL ? FAILURE : SUCCESS;
}

char *Parser::parsing(const char *expression) {
  std::stack<char> stack;
  char *rpn = (char *)calloc(512, sizeof(char));
  int i = 0;
  int j = 0;
  char c;
  while ((c = expression[i]) != '\0') {
    if (v->isLBracket(c)) {
      stack.push(c);
    }
    if (v->isDigit(c) || v->isX(c)) {
      while (v->isDigit(c) || v->isPoint(c) || v->isX(c)) {
        rpn[j++] = c;
        c = expression[++i];
      }
      rpn[j++] = ' ';
    }
    if (v->isRBracket(c)) {
      while (!stack.empty() && !v->isLBracket(stack.top())) {
        rpn[j++] = stack.top();
        stack.pop();
      }
      stack.pop();
    }
    if (c != '\0' &&
        (v->isOperator(c) || v->isPow(c) || v->isMod(expression, i))) {
      if (v->isUnar(c) && v->checkUnar(expression, i)) {
        c = (c == '-') ? '~' : c;
      }
      if (!stack.empty() &&
          (stack.top() == '\0' || v->isLBracket(stack.top()))) {
        stack.push(c);
      } else {
        if (!stack.empty() && checkPriority(c, stack.top())) {
          rpn[j++] = stack.top();
          stack.pop();
          if (!stack.empty() && stack.top() == '~') {
            rpn[j++] = stack.top();
            stack.pop();
          } else {
            rpn[j++] = ' ';
          }
          stack.push(c);
        } else {
          stack.push(c);
        }
      }
    }
    if (c != '\0' && v->isFirstLetFunc(c)) {
      char tmp[6] = {0};
      v->subFu(expression, i, tmp);
      stack.push(getLetFun(tmp));
      i += strlen(tmp) - 1;
    }
    if (c == '\0') break;
    i++;
  }
  while (!stack.empty()) {
    rpn[j++] = stack.top();
    stack.pop();
  }
  deleteExtraSpases(rpn);
  return rpn;
}

void Parser::deleteExtraSpases(char *rpn) {
  char ptr[1000] = {0};
  strcpy(ptr, rpn);
  char *delim = strtok(ptr, " ");
  while (delim != NULL) {
    strcpy(rpn, delim);
    rpn += strlen(delim);
    *rpn++ = ' ';
    delim = strtok(NULL, " ");
  }
  *rpn = '\0';
}

char Parser::getLetFun(char *function) {
  char c = '\0';
  if (!strcmp(function, "sin")) c = 's';
  if (!strcmp(function, "cos")) c = 'c';
  if (!strcmp(function, "tan")) c = 't';
  if (!strcmp(function, "asin")) c = 'S';
  if (!strcmp(function, "acos")) c = 'C';
  if (!strcmp(function, "atan")) c = 'T';
  if (!strcmp(function, "ln")) c = 'l';
  if (!strcmp(function, "log")) c = 'L';
  if (!strcmp(function, "sqrt")) c = 'q';
  return c;
}

int Parser::checkPriority(char inExp, char inSt) {
  return getPriority(inExp) <= getPriority(inSt);
}

int Parser::getPriority(char c) {
  int result = 0;
  if (c == '*' || c == '/') result = 1;
  if (c == 'm') result = 2;
  if (v->isPow(c)) result = 3;
  if (v->isFirstLetFunc(c)) result = 4;
  if (c == '~') result = 5;
  return result;
}

void Credit::creditCalc(double sum, int month, double rate, int type,
                        DataCred *data) {
  if (type == 1) {
    anuitet(sum, month, rate, data);
  } else {
    different(sum, month, rate, data);
  }
}

void Credit::anuitet(double sum, int month, double rate, DataCred *data) {
  double R_m = rate / 12 / 100;
  double K_a = R_m * pow(1 + R_m, month) / (pow(1 + R_m, month) - 1);
  data->payment = sum * K_a;
  data->total_payment = data->payment * month;
  data->overpayment = data->total_payment - sum;
}

void Credit::different(double sum, int month, double rate, DataCred *data) {
  double main_deb_month = sum / month;
  data->first_payment = 0;
  data->last_payment = 0;
  data->total_payment = 0;
  data->overpayment = 0;
  double main_rest = sum;
  rate /= 100;
  for (int i = 0; i < month; i++) {
    double percent_month = 0;
    percent_month = main_rest * rate * MONTH / 365;
    double platez = main_deb_month + percent_month;
    if (i == 0) {
      data->first_payment = platez;
    }
    if (i == month - 1) {
      data->last_payment = platez;
    }
    data->total_payment += platez;
    main_rest -= main_deb_month;
  }
  data->overpayment = data->total_payment - sum;
}

void Deposit::depositCalc(double deposit_start, int period, double rate,
                          double key_rate, char *capital, char *payout,
                          char *replenishment, double tax_type,
                          double replenish, DataDep *data) {
  data->deposit_start = deposit_start;
  data->period = period;
  data->rate = rate;
  data->key_rate = key_rate;
  data->capital = capital;
  data->payout = payout;
  data->replenishment = replenishment;
  data->tax_type = tax_type;
  data->replenish = replenish;

  data->percent = 0;
  data->deposit_end = data->deposit_start;
  data->tax = 0;

  if (!strcmp(data->capital, WORD)) {
    withoutCapitalisation(data);
  } else {
    withCapitalisation(data);
  }
}

void Deposit::withCapitalisation(DataDep *data) {
  int period_capit = getStatus(data->capital);
  int period = 0;
  if (strcmp(data->replenishment, WORD) != 0) {
    period = getStatus(data->replenishment);
  }
  for (int i = period_capit; i <= data->period; i += period_capit) {
    if (strcmp(data->replenishment, WORD) != 0 && i >= period) {
      data->deposit_end += data->replenish;
    }
    data->deposit_end +=
        calculatePercent(data->deposit_end, data->rate, period_capit);
  }
  data->percent = data->deposit_end - data->deposit_start;
}

void Deposit::withoutCapitalisation(struct DataDep *data) {
  data->percent =
      calculatePercent(data->deposit_start, data->rate, data->period);
  data->deposit_end = data->deposit_start + data->percent;
  if (strcmp(data->replenishment, WORD) != 0) {
    calcReplWithoutCapitalisation(data);
  }
  if (data->rate > data->key_rate) {
    calculateTax(data);
  }
}

void Deposit::calculateTax(DataDep *data) {
  double tax_dif = 0;
  tax_dif = calculatePercent(data->deposit_start, data->key_rate, data->period);
  data->tax = data->tax_type / 100.0 * (data->percent - tax_dif);
  data->percent -= data->tax;
  data->deposit_end -= data->tax;
}

void Deposit::calcReplWithoutCapitalisation(DataDep *data) {
  int period = getStatus(data->replenishment);
  double added_percent = 0;
  int additional_deposit = 0;
  for (int i = period; i < data->period; i += period) {
    additional_deposit += data->replenish;
    added_percent += calculatePercent(data->replenish, data->rate, i);
  }
  data->percent += added_percent;
  data->deposit_end += added_percent + additional_deposit;
}

int Deposit::getStatus(char *str) {
  int res = 0;
  if (!strcmp(str, "ежемесячно")) {
    res = 1;
  } else if (!strcmp(str, "3 месяца")) {
    res = 3;
  } else if (!strcmp(str, "6 месяцев")) {
    res = 6;
  } else if (!strcmp(str, "1 год")) {
    res = 12;
  }
  return res;
}

double Deposit::calculatePercent(int deposit_start, double rate, int period) {
  return deposit_start * rate / 100.0 * period * MONTH / 365;
}
