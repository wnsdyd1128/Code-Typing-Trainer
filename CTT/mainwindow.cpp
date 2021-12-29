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
  countCorrectWord = 0;
  countWrongWord = 0;
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
      applyToResult(v.at(currentIndex), ui->myLineEdit->text()); // 마지막 입력에 대한 별도 처리
      applyToFigure();
    }
  QTime stopwatch(0, remainMinute, remainSecond);
  QString mask = stopwatch.toString("mm : ss");
  ui->lcdRemainTime->display(mask);
  setRemainSecond(remainSecond - 1);
  holdingTime++;
}
void MainWindow::on_startButton_clicked()
{
  startFlag = true;
  applyComboBoxToLimitTime();
  ui->stackedWidget->setCurrentIndex(1);
  ui->currentCode->setText(v.at(0));
  ui->nextCode->setText(v.at(1));
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
  QPixmap timerImage(currentPath + "/sand-clock.png");
  QPixmap accuracyImage(currentPath + "/accuracy.png");
  QPixmap speedImage(currentPath + "/speed.png");
  this->setWindowIcon(mainwindowIcon);
  this->setWindowTitle("Code Typing Trainer by JYP");
  int w = ui->timerIcon->width();
  int h = ui->timerIcon->height();
  ui->timerIcon->setPixmap(timerImage.scaled(w, h, Qt::KeepAspectRatio));
  w = ui->remainTimeImage->width();
  h = ui->remainTimeImage->height();
  ui->remainTimeImage->setPixmap(timerImage.scaled(w, h, Qt::KeepAspectRatio));
  w = ui->speedIcon->width();
  h = ui->speedIcon->height();
  ui->speedIcon->setPixmap(speedImage.scaled(w, h, Qt::KeepAspectRatio));
  w = ui->accuracyIcon->width();
  h = ui->accuracyIcon->height();
  ui->accuracyIcon->setPixmap(accuracyImage.scaled(w, h, Qt::KeepAspectRatio));

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
  QString iptCode = ui->myLineEdit->text();
  applyToResult(curCode, iptCode);
  incrementIndex(prevIndex);
  incrementIndex(currentIndex);
  incrementIndex(nextIndex);
  prvCode = v.at(prevIndex);
  curCode = v.at(currentIndex);
  nxtCode = v.at(nextIndex);
  ui->prevCode->setText(prvCode);
  ui->currentCode->setText(curCode);
  ui->nextCode->setText(nxtCode);
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
void MainWindow::applyToResult(const QString& sample, const QString& input){
  QStringList sampleList = sample.split(" ");
  QStringList inputList = input.split(" ");
  if(sampleList.size() != inputList.size()){
      int length;
      if(sampleList.size() < inputList.size())
        length = sampleList.size();
      else
        length = inputList.size();
      for(int i = 0; i < length; i++){
          if(sampleList.at(i) != inputList.at(i))
            countWrongWord++;
          else
            countCorrectWord++;
        }
      countWrongWord += abs(sampleList.size() - inputList.size());
    }
  else{
      for(int i = 0; i < sampleList.size(); i++){
          if(sampleList.at(i) != inputList.at(i))
            countWrongWord++;
          else
            countCorrectWord++;
        }
    }
}

void MainWindow::applyToFigure(){
  uint32_t countTotalWord = countWrongWord + countCorrectWord;
  speed = (countTotalWord) / static_cast<double>(limitTime);
  accuracy = countCorrectWord / static_cast<double>(countTotalWord);
  QString speedString = QString::number(speed * 100, 'f', 0);
  QString accuracyString = QString::number(accuracy * 100, 'f', 0);
  ui->speedFigure->setText(speedString + " WPM");
  ui->accuracyFigure->setText(accuracyString + " %");
}
