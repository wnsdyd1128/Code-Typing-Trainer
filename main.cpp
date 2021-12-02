#include "mainwindow.h"
#include "resultscreen.h"
#include "testscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
