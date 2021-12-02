#include "resultscreen.h"
#include "ui_resultscreen.h"

ResultScreen::ResultScreen(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ResultScreen)
{
  ui->setupUi(this);
  QPixmap timerIcon("C:\\Users\\ERC\\Documents\\Qt\\CTT\\sand-clock.png");
  this->setWindowTitle("Code Typing Trainer by JYP");
}

ResultScreen::~ResultScreen()
{
  delete ui;
}

void ResultScreen::on_retryButton_clicked()
{

}


void ResultScreen::on_closeButton_clicked()
{
}

