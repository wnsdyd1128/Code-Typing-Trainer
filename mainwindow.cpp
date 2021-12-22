#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QPixmap mainwindowIcon("C:\\Users\\ERC\\Documents\\Qt\\CTT\\text-box.png");
  QPixmap timerIcon("C:\\Users\\ERC\\Documents\\Qt\\CTT\\sand-clock.png");
  this->setWindowIcon(mainwindowIcon);
  this->setWindowTitle("Code Typing Trainer by JYP");
  int w = ui->timerIcon->width();
  int h = ui->timerIcon->height();
  ui->timerIcon->setPixmap(timerIcon.scaled(w, h, Qt::KeepAspectRatio));
  ui->stackedWidget->setCurrentIndex(0);
  ui->myLineEdit->installEventFilter(this);
  w = ui->remainTimeImage->width();
  h = ui->remainTimeImage->height();

  ui->remainTimeImage->setPixmap(timerIcon.scaled(w, h, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::applyComboBoxToLimitTime(){
  QString curText = ui->comboBox->currentText();
  if(curText == "1 Minute")
    setTimeVariable(1 * 60);
  else if(curText == "3 Minute")
    setTimeVariable(3 * 60);
  else if(curText == "5 Minute")
    setTimeVariable(5 * 60);
  holdingTime = 0;
  timer = std::make_shared<QTimer>();
  connect(timer.get(), SIGNAL(timeout()), this, SLOT(check()));
  timer->start(1000);
}
void MainWindow::setTimeVariable(int time){
  limitTime = time;
  int m = time / 60;
  int s = time % 60;
  setRemainMinute(m);
  setRemainSecond(s);
  setHoldingTime(0);
}

void MainWindow::check(){
  if(holdingTime >= limitTime){
      ui->stackedWidget->setCurrentIndex(2);
      timer->stop();
    }
  QTime stopwatch(0, remainMinute, remainSecond);
  QString mask = stopwatch.toString("mm : ss");
  ui->lcdRemainTime->display(mask);
  remainSecond--;
  holdingTime++;
}
void MainWindow::on_startButton_clicked()
{
  applyComboBoxToLimitTime();
  ui->stackedWidget->setCurrentIndex(1);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
  if(obj == ui->myLineEdit){
      if(event->type() == QEvent::KeyPress){
          QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
          if(keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Left){
              return true;
            }
        }
      else if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonRelease
              || event->type() == QEvent::MouseButtonDblClick){
          return true;
        }
    }
  return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setRemainMinute(int m){
  remainMinute = m;
}

void MainWindow::setRemainSecond(int s){
  int second;
  if(s == 0) {
      setRemainMinute(remainMinute - 1);
      second = 60;
    }
  else {
      second = s;
    }
  remainSecond = second;
}

void MainWindow::setHoldingTime(int h){
  holdingTime = h;
}

void MainWindow::on_buttonBox_accepted()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonBox_rejected()
{
  this->close();
}

