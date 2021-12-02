#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include <QtGui>
#include "testscreen.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setLimitTime(int);
  int getLimitTime();
  void applyComboBoxToLimitTime();
private slots:
  void on_startButton_clicked();

private:
  Ui::MainWindow *ui;
  QTimer *timer;
  int limitTime;
  TestScreen *ts;
};
#endif // MAINWINDOW_H
