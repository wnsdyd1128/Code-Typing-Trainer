#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QFile>
namespace Ui {
  class TestScreen;
}

class TestScreen : public QDialog
{
  Q_OBJECT

public:
  explicit TestScreen(QWidget *parent = nullptr);
  ~TestScreen();
  void setRemainTime(int);
  void setRemainMinute(int);
  void setRemainSecond(int);
  void setHoldingTime(int);
  int getHoldingTime();
  int getRemainMinute();
  int getRemainSecond();
  bool isHolded();
private:
  Ui::TestScreen *ui;
  ResultScreen *rs;
  int remainMinute;
  int remainSecond;
  std::shared_ptr<QTimer> timer;
  int holdingTime = 0;
  int countWord;
  int countCorrect;
  int countWrong;
  void check();
  void goResultScreen();
signals:
  void timeSignals();
public slots:
  void timerCallBack();
};

#endif // TESTSCREEN_H
