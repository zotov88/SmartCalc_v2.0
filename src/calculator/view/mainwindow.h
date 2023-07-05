#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>

#include "../controller/controller.h"
#include "../model/model.h"
#include "creditcalc.h"
#include "depositcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void getValueFromButtonFunc();
  void getValFromButtonOther();
  void on_bt_equal_clicked();
  void on_bt_AC_clicked();
  void on_bt_bcsp_clicked();
  void on_bt_up_clicked();
  void on_depoz_triggered();
  void on_action_triggered();

  void on_bt_graph_clicked();

 private:
  s21::Calculator calc_model;
  s21::Parser p_model;
  s21::Validation v_model;
  Ui::MainWindow *ui;
  Creditcalc *cWindow;
  Depositcalc *dWindow;
};

#endif  // MAINWINDOW_H
