#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class Depositcalc;
}

QString point_pars(QString str);

class Depositcalc : public QWidget {
  Q_OBJECT

 public:
  explicit Depositcalc(QWidget *parent = nullptr);
  ~Depositcalc();

 signals:
  void secondWindow();

 private slots:
  void on_lineEdit_dep_editingFinished();
  void on_pushButton_2_clicked();
  void on_bt_calc_clicked();
  char *getPointerChar(QString str);
  QString swichPoint(QString str);

 private:
  Ui::Depositcalc *ui;
};

#endif  // DEPOSITCALC_H
