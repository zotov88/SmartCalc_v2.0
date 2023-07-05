#include "depositcalc.h"

#include "../controller/controller.h"
#include "ui_depositcalc.h"

Depositcalc::Depositcalc(QWidget* parent)
    : QWidget(parent), ui(new Ui::Depositcalc) {
  ui->setupUi(this);
  on_lineEdit_dep_editingFinished();
}

Depositcalc::~Depositcalc() { delete ui; }

void Depositcalc::on_lineEdit_dep_editingFinished() {
  ui->lineEdit_dep->setValidator(new QIntValidator(0, 100000000, this));
  ui->lineEdit_period->setValidator(new QIntValidator(0, 100000000, this));
  ui->lineEdit_rate->setValidator(new QDoubleValidator(0, 0, 2, this));
  ui->lineEdit_key_rate->setValidator(new QDoubleValidator(0, 0, 2, this));
  ui->lineEdit_tax_kind->setValidator(new QDoubleValidator(0, 0, 2, this));
  ui->lineEdit_replenish->setValidator(new QDoubleValidator(0, 0, 2, this));
}

void Depositcalc::on_pushButton_2_clicked() {
  ui->lineEdit_dep->clear();
  ui->lineEdit_period->clear();
  ui->lineEdit_rate->clear();
  ui->lineEdit_key_rate->clear();
  ui->lineEdit_tax_kind->clear();
  ui->lineEdit_am_money->clear();
  ui->lineEdit_am_rate->clear();
  ui->lineEdit_am_tax->clear();
  ui->lineEdit_replenish->clear();
}

char* Depositcalc::getPointerChar(QString str) {
  QByteArray ba = str.toLocal8Bit();
  return ba.data();
}

void Depositcalc::on_bt_calc_clicked() {
  s21::Deposit dmodel;
  s21::DepositController controller(&dmodel);
  s21::Deposit::DataDep data;
  double money = ui->lineEdit_dep->text().toInt();
  double period = ui->lineEdit_period->text().toInt();
  double rate = swichPoint(ui->lineEdit_rate->text()).toDouble();
  double key_rate = swichPoint(ui->lineEdit_key_rate->text()).toDouble();

  QByteArray ba1 = ui->box_payout->currentText().toLocal8Bit();
  char* payout = ba1.data();
  QByteArray ba2 = ui->box_replenishment->currentText().toLocal8Bit();
  char* replenishment = ba2.data();
  QByteArray ba3 = ui->box_capitalisation->currentText().toLocal8Bit();
  char* capitalisation = ba3.data();

  double tax_type = swichPoint(ui->lineEdit_tax_kind->text()).toDouble();
  double replenish = swichPoint(ui->lineEdit_replenish->text()).toDouble();
  controller.depositCalc(money, period, rate, key_rate, capitalisation, payout,
                         replenishment, tax_type, replenish, &data);
  ui->lineEdit_am_money->setText(QString::number(data.deposit_end, 'g', 8));
  ui->lineEdit_am_rate->setText(QString::number(data.percent));
  ui->lineEdit_am_tax->setText(QString::number(data.tax));
}

QString Depositcalc::swichPoint(QString str) {
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ',') {
      str[i] = '.';
    }
  }
  return str;
}
