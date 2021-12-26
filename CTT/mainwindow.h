#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include <QtGui>
#include <QLineEdit>
#include <QStackedWidget>
#include <QString>
#include <QVector>
#include <QFile>
#include <QApplication>
#include <iostream>
#include <QSyntaxHighlighter>
//#include "qth.h"
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
  void setImage();
  void setFile();
  void incrementIndex(uint32_t&);
  void decrementIndex(uint32_t&);
  void applyToResult(const QStringList&, const QStringList&);
private slots:
  void on_startButton_clicked();
  void check();
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
  void showTypingCode();
private:
  Ui::MainWindow *ui;
  std::shared_ptr<QTimer> timer;
  QVector<QString> v;
  int holdingTime;
  int remainMinute;
  int remainSecond;
  int limitTime;
  uint32_t prevIndex;
  uint32_t currentIndex;
  uint32_t nextIndex;
  int countCorrectWord;
  int countWord;
  double accuracy;
  double speed;
  bool startFlag;
//  qTh* thread;
protected:
  bool eventFilter(QObject* obj, QEvent* event);
};
#endif // MAINWINDOW_H
