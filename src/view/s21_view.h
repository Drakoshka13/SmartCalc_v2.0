#ifndef VIEW_S21_VIEW_H
#define VIEW_S21_VIEW_H

#include <QMainWindow>
#include <QVector>

#include "../controller/s21_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void SetMounthPay(std::pair<double, double> month_pay);
  void SetPercents(double percents);
  void SetResSum(double sum);

 private:
  Ui::MainWindow *ui;
  Controller controller_;
  int len_chek = 0;
  int last_element_len = 0;
  int pay_type = 0;
  std::string credit_sum, credit_time, credit_rate;
  std::string deposit_sum, deposit_time, deposit_rate, deposit_tax_rate;
  bool capitalization = false;
  int payment_period = 0;

  std::string GetInputString();
  std::string GetInputXMin();
  std::string GetInputXMax();
  std::string GetInputYMin();
  std::string GetInputYMax();

 private slots:
  void digits_numbers();
  void clear_button();
  void delete_element();
  void go_to_res();
  void make_graph();
  void AN_clicked();
  void DI_clicked();
  void credit_res_clicked();
  void depos_res_clicked();
  void day_clicked();
  void month_clicked();
  void kvart_clicked();
};
}  // namespace s21

#endif  // VIEW_S21_VIEW_H
