#ifndef RESULTSCREEN_H
#define RESULTSCREEN_H

#include <QDialog>
namespace Ui {
  class ResultScreen;
}

class ResultScreen : public QDialog
{
  Q_OBJECT

public:
  explicit ResultScreen(QWidget *parent = nullptr);
  ~ResultScreen();

private slots:
  void on_retryButton_clicked();

  void on_closeButton_clicked();

private:
  Ui::ResultScreen *ui;
  double accuracy;
  double speed;

};

#endif // RESULTSCREEN_H
