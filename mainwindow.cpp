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
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::applyComboBoxToLimitTime(){
  QString curText = ui->comboBox->currentText();
  if(curText == "1 Minute")
    setLimitTime(1 * 60);
  else if(curText == "3 Minute")
    setLimitTime(3 * 60);
  else if(curText == "5 Minute")
    setLimitTime(5 * 60);
}
void MainWindow::setLimitTime(int lt){
  limitTime = lt;
}

int MainWindow::getLimitTime(){
  return limitTime;
}

void MainWindow::on_startButton_clicked()
{
  applyComboBoxToLimitTime();
  ts = new TestScreen(this);
  ts->setRemainTime(limitTime);
  hide();
  ts->show();
}
