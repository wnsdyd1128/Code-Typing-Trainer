#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setImage();
  setFile();
  ui->stackedWidget->setCurrentIndex(0);
  currentIndex = 0;
  prevIndex = currentIndex;
  decrementIndex(prevIndex);
  nextIndex = currentIndex + 1;
  startFlag = false;
  ui->myLineEdit->installEventFilter(this);
  connect(ui->myLineEdit, &QLineEdit::returnPressed, this, &MainWindow::showTypingCode);
//  thread = new qTh(this);
//  connect(thread, SIGNAL(setTypingCode(QString)), this, SLOT(showTypingCode(QString)));
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
//  connect(timer.get(), SIGNAL(timeout()), this, SLOT(check()));
  connect(timer.get(), &QTimer::timeout, this, &MainWindow::check);
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
//      thread->requestInterruption(); // Interrupt!
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
  startFlag = true;
  applyComboBoxToLimitTime();
  ui->stackedWidget->setCurrentIndex(1);
  showTypingCode();
//  thread->start();
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
  ui->myLineEdit->clear();
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonBox_rejected()
{
  this->close();
}

void MainWindow::setImage(){
  QString currentPath = QApplication::applicationDirPath();
  QPixmap mainwindowIcon(currentPath + "/text-box.png");
  QPixmap timerIcon(currentPath + "/sand-clock.png");
  this->setWindowIcon(mainwindowIcon);
  this->setWindowTitle("Code Typing Trainer by JYP");
  int w = ui->timerIcon->width();
  int h = ui->timerIcon->height();
  ui->timerIcon->setPixmap(timerIcon.scaled(w, h, Qt::KeepAspectRatio));
  w = ui->remainTimeImage->width();
  h = ui->remainTimeImage->height();
  ui->remainTimeImage->setPixmap(timerIcon.scaled(w, h, Qt::KeepAspectRatio));

}

void MainWindow::showTypingCode(){
//  unsigned int nextIndex = (thread->getCurrentIndex() + 1) % (thread->getSize());
//  ui->currentCode->insertPlainText(curCode);
//  QString nxtCode = thread->getQString(nextIndex);
//  ui->nextCode->insertPlainText(nxtCode);
//  std::cout << "Enter Pressed" << std::endl;
  QString prvCode = v.at(prevIndex);
  QString curCode = v.at(currentIndex);
  QString nxtCode = v.at(nextIndex);

  if(!startFlag){
      ui->prevCode->setText(prvCode);
    }
  else{
      startFlag = false;
    }
  ui->currentCode->setText(curCode);
  ui->nextCode->setText(nxtCode);
  incrementIndex(prevIndex);
  incrementIndex(currentIndex);
  incrementIndex(nextIndex);
  ui->myLineEdit->clear();
}

void MainWindow::setFile(){
  QString currentPath = QApplication::applicationDirPath(); // 현재 프로그램 경로
  QFile file(currentPath + "/sampleCode.txt");
  currentIndex = 0;
  nextIndex = currentIndex + 1;
  if(file.open(QFile::ReadOnly | QFile::Text)){
      if(file.exists()){
          QTextStream openFile(&file);
          QString str;
          while(!openFile.atEnd()){
              str = openFile.readLine();
              v.push_back(str);
            }
          file.close();
        }
      else{
          qDebug() << "File does not exist \n ";
        }
    }
}

void MainWindow::incrementIndex(uint32_t& idx){
  size_t size = v.size();
  idx = (idx + 1) % size; // idx++ if(idx >= size) idx = 0;
}

void MainWindow::decrementIndex(uint32_t& idx){
  size_t size = v.size();
  idx = (idx + size - 1) % size; // idx-- if(idx < 0) idx = size - 1;
}
void MainWindow::applyToResult(const QStringList& sample, const QStringList& input){

}
