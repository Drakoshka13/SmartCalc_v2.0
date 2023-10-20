
#include "s21_view.h"

#include <qdebug.h>
#include <string.h>

#include <QVector>
#include <iostream>

#include "ui_mainwindow.h"
using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_stepen, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_bracket1, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_bracket2, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tg, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atg, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clear_button()));
  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(delete_element()));
  connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(go_to_res()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(make_graph()));
  connect(ui->credit_result, SIGNAL(clicked()), this,
          SLOT(credit_res_clicked()));
  connect(ui->ann_pay, SIGNAL(clicked()), this, SLOT(AN_clicked()));
  connect(ui->dif_pay, SIGNAL(clicked()), this, SLOT(DI_clicked()));
  connect(ui->pushButton_deposit_result, SIGNAL(clicked()), this,
          SLOT(depos_res_clicked()));
  connect(ui->radioButton_day, SIGNAL(clicked()), this, SLOT(day_clicked()));
  connect(ui->radioButton_month, SIGNAL(clicked()), this,
          SLOT(month_clicked()));
  connect(ui->radioButton_kvart, SIGNAL(clicked()), this,
          SLOT(kvart_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  int len_px = button->text().length();
  if (len_chek == 0) {
    ui->Input_Window->setText("");
  }
  len_chek += len_px;
  last_element_len = len_px;  // стирать функцию целиком?
  QString all_numbers;
  all_numbers = (ui->Input_Window->text() + button->text());
  ui->Input_Window->setText(all_numbers);
}

void MainWindow::clear_button() {
  ui->Input_Window->clear();
  ui->Input_Window->setText("0");
  len_chek = 0;
  ui->widget->clearGraphs();
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, false);
  ui->widget->setInteraction(QCP::iRangeDrag, false);
}

void MainWindow::delete_element() {
  QString new_text =
      ui->Input_Window->text().left(std::size(ui->Input_Window->text()) - 1);
  ui->Input_Window->setText(new_text);
}

std::string MainWindow::GetInputString() {
  QString text = ui->Input_Window->text();
  return text.toStdString();
}
std::string MainWindow::GetInputXMin() {
  return ui->Input_X_min->text().toStdString();
}

std::string MainWindow::GetInputXMax() {
  return ui->Input_X_max->text().toStdString();
}

std::string MainWindow::GetInputYMin() {
  return ui->Input_Y_min->text().toStdString();
}

std::string MainWindow::GetInputYMax() {
  return ui->Input_Y_max->text().toStdString();
}

void MainWindow::go_to_res() {
  std::string text_str = ui->Input_Window->text().toStdString();
  std::string x_str = ui->Input_X->text().toStdString();
  try {
    double res = controller_.Calculate(text_str, x_str);
    ui->Input_Window->setText(QString::number(res, 'g', 7));
    len_chek = 0;
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Error", e.what());
    clear_button();
  }
}

void MainWindow::make_graph() {
  ui->widget->clearGraphs();
  std::string text_str = ui->Input_Window->text().toStdString();
  std::string x_min = ui->Input_X_min->text().toStdString();
  std::string x_max = ui->Input_X_max->text().toStdString();
  std::string y_min = ui->Input_Y_min->text().toStdString();
  std::string y_max = ui->Input_Y_max->text().toStdString();
  try {
    std::pair<std::vector<double>, std::vector<double>> Point =
        controller_.Graph(text_str, x_min, x_max, y_min, y_max);
    QVector<double> x(Point.first.begin(), Point.first.end());
    QVector<double> y(Point.second.begin(), Point.second.end());
    ui->widget->xAxis->setRange(atof(x_min.c_str()), atof(x_max.c_str()));
    ui->widget->yAxis->setRange(atof(y_min.c_str()), atof(y_max.c_str()));
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Error", e.what());
    clear_button();
  }
}

void MainWindow::AN_clicked() { pay_type = 1; }

void MainWindow::DI_clicked() { pay_type = 2; }

void MainWindow::SetMounthPay(std::pair<double, double> month_pay) {
  double mes_plata_max = month_pay.first, mes_plata_min = month_pay.second;
  if (this->pay_type == 2) {
    ui->month_pay->setText(
        QString::number(round(mes_plata_max * 100) / 100, 'g', 16) + " -> " +
        QString::number(round(mes_plata_min * 100) / 100, 'g', 16));
  } else {
    ui->month_pay->setText(
        QString::number(round(mes_plata_max * 100) / 100, 'g', 16));
  }
}

void MainWindow::SetPercents(double percents) {
  ui->credit_percents->setText(
      QString::number(round(percents * 100) / 100, 'g', 16));
}

void MainWindow::SetResSum(double sum) {
  ui->all_credit_sum->setText(QString::number(round(sum * 100) / 100, 'g', 16));
}

void MainWindow::credit_res_clicked() {
  credit_sum = ui->Credit_sum->text().toStdString();
  credit_time = ui->Credit_time->text().toStdString();
  credit_rate = ui->Credit_rate->text().toStdString();

  ui->Credit_rate->setText("");
  ui->Credit_time->setText("");
  ui->Credit_sum->setText("");

  try {
    CreditResult r =
        controller_.Credit(pay_type, credit_sum, credit_time, credit_rate);
    SetMounthPay(r.pay);
    SetPercents(r.perc);
    SetResSum(r.res_sum);
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Error", e.what());
  }
}

void MainWindow::day_clicked() { payment_period = 1; }

void MainWindow::month_clicked() { payment_period = 2; }

void MainWindow::kvart_clicked() { payment_period = 3; }

void MainWindow::depos_res_clicked() {
  ui->tax_rate->setText("7.5");

  deposit_sum = ui->deposit_sum->text().toStdString();
  deposit_time = ui->deposit_time->text().toStdString();
  deposit_rate = ui->deposit_rate->text().toStdString();
  deposit_tax_rate = ui->tax_rate->text().toStdString();
  ui->deposit_sum->setText("");
  ui->deposit_time->setText("");
  ui->deposit_rate->setText("");
  ui->tax_rate->setText("7.5");
  capitalization = (ui->checkBox_capital->isChecked()) ? true : false;
  try {
    DeposResult r =
        controller_.Deposit(capitalization, payment_period, deposit_sum,
                            deposit_time, deposit_rate, deposit_tax_rate);
    ui->res_depos_sum->setText(
        QString::number(round(r.sum * 100) / 100, 'g', 16));
    ui->depos_percents->setText(
        QString::number(round(r.perc * 100) / 100, 'g', 16));
    ui->minus_tax->setText(QString::number(round(r.tax * 100) / 100, 'g', 16));
  } catch (std::exception &e) {
    QMessageBox::critical(this, "Error", e.what());
  }
}
