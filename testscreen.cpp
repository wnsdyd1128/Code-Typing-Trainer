#include "testscreen.h"
#include "ui_testscreen.h"

TestScreen::TestScreen(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TestScreen)
{
  ui->setupUi(this);
  QPixmap timerIcon("C:\\Users\\ERC\\Documents\\Qt\\CTT\\sand-clock.png");
  this->setWindowTitle("Code Typing Trainer by JYP");
  bool flag = false;
  if(flag) {

    }
  int w = ui->remainTimeImage->width();
  int h = ui->remainTimeImage->height();
  ui->remainTimeImage->setPixmap(timerIcon.scaled(w, h, Qt::KeepAspectRatio));
  timer = std::make_shared<QTimer>();
  connect(timer.get(), SIGNAL(timeout()), this, SLOT(timerCallBack()));
  timer->start(1000);
  connect(this, SIGNAL(timesignals()), this, SLOT(goResultScreen()));
}

TestScreen::~TestScreen()
{
  delete ui;
}

void TestScreen::setRemainTime(int time){
  int minute = time / 60;
  int second = time % 60;
  setHoldingTime(0);
  setRemainMinute(minute);
  setRemainSecond(second);
}

void TestScreen::setRemainMinute(int m){
  remainMinute = m;
}

void TestScreen::setRemainSecond(int s){
  int second;
  if(s == 0) {
      int minute = getRemainMinute();
      minute--;
      setRemainMinute(minute);
      second = 60;
    }
  else {
      second = s;
    }
  remainSecond = second;
}

void TestScreen::setHoldingTime(int t){
  holdingTime = t;
}
int TestScreen::getRemainMinute(){
  return remainMinute;
}

int TestScreen::getRemainSecond(){
  return remainSecond;
}

int TestScreen::getHoldingTime(){
  return holdingTime;
}
void TestScreen::timerCallBack(){
  QTime time(0, remainMinute, remainSecond);
  QString time_text = time.toString("mm : ss");
  ui->lcdRemainTime->display(time_text);
  setRemainSecond(getRemainSecond() - 1);
  setHoldingTime(getHoldingTime() + 1);
}

bool TestScreen::isHolded(){
  return holdingTime ? true : false;
}

void TestScreen::check(){
  bool isTimeOut = (!(remainMinute && remainSecond));
  if(isTimeOut && isHolded()){
      emit timeSignals();
    }
}


void TestScreen::goResultScreen(){
  rs = new ResultScreen(this);
  rs->show();
  hide();
}
