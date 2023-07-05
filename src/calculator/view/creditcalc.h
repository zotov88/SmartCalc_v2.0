#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class Creditcalc;
}

class Creditcalc : public QWidget {
  Q_OBJECT

 public:
  explicit Creditcalc(QWidget *parent = 0);
  ~Creditcalc();
  Ui::Creditcalc *ui;

 signals:
  void firstWindow();

 private slots:
  void on_bt_calc_clicked();
  void on_bt_clear_clicked();

 private:
  void setVisibleFieldsTrue();
  void setVisibleFieldsFalse();
};

#endif  // CREDITCALC_H
