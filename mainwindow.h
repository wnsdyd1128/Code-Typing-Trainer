#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include <QtGui>
#include <QLineEdit>
#include "testscreen.h"
#include <QStackedWidget>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setTimeVariable(int);
  void applyComboBoxToLimitTime();
  void setHoldingTime(int);
  void setRemainMinute(int);
  void setRemainSecond(int);
private slots:
  void on_startButton_clicked();
  void check();
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::MainWindow *ui;
  std::shared_ptr<QTimer> timer;
  int holdingTime;
  int remainMinute;
  int remainSecond;
  int limitTime;
  int countCorrectWord;
  int countWord;
  double accuracy;
  double speed;
protected:
  bool eventFilter(QObject* obj, QEvent* event);
};
#endif // MAINWINDOW_H
