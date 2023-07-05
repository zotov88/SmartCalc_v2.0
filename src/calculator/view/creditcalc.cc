#include "creditcalc.h"

#include "../controller/controller.h"
#include "ui_creditcalc.h"

Creditcalc::Creditcalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::Creditcalc) {
  ui->setupUi(this);
}

Creditcalc::~Creditcalc() { delete ui; }

void Creditcalc::on_bt_calc_clicked() {
  s21::Credit cmodel;
  s21::CreditController controller(&cmodel);
  s21::Credit::DataCred data;
  setVisibleFieldsFalse();
  setVisibleFieldsTrue();

  int sum = ui->sp_sum->value();
  int month = ui->sp_month->value();
  double percent = ui->db_sp_percent->value();
  int type = ui->rb_dif->isChecked() ? 2 : 1;
  controller.creditCalc(sum, month, percent, type, &data);
  ui->le_total->setText(QString::number((int)data.total_payment));
  ui->le_overpayment->setText(QString::number((int)data.overpayment));
  ui->le_payment->setText(QString::number((int)data.payment));
  ui->le_payment_first->setText(QString::number((int)data.first_payment));
  ui->le_payment_last->setText(QString::number((int)data.last_payment));
}

void Creditcalc::setVisibleFieldsTrue() {
  if (ui->rb_dif->isChecked()) {
    ui->le_payment_first->setVisible(true);
    ui->label_6->setVisible(true);
    ui->le_payment_last->setVisible(true);
    ui->label_7->setVisible(true);
  }
  if (ui->rb_ann->isChecked()) {
    ui->le_payment->setVisible(true);
    ui->label_5->setVisible(true);
  }
}

void Creditcalc::setVisibleFieldsFalse() {
  ui->le_payment_first->setVisible(false);
  ui->label_6->setVisible(false);
  ui->le_payment_last->setVisible(false);
  ui->label_7->setVisible(false);
  ui->le_payment->setVisible(false);
  ui->label_5->setVisible(false);
}

void Creditcalc::on_bt_clear_clicked() {
  ui->sp_sum->setValue(1);
  ui->sp_month->setValue(1);
  ui->db_sp_percent->setValue(1);
  ui->le_total->setText("");
  ui->le_overpayment->setText("");
  ui->le_payment->setText("");
  ui->le_payment_first->setText("");
  ui->le_payment_last->setText("");
  ui->le_payment_first->setVisible(false);
  ui->label_6->setVisible(false);
  ui->le_payment_last->setVisible(false);
  ui->label_7->setVisible(false);
  ui->le_payment->setVisible(false);
  ui->label_5->setVisible(false);
}
