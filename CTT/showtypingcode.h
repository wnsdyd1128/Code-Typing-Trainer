#ifndef SHOWTYPINGCODE_H
#define SHOWTYPINGCODE_H

#include <QThread>
#include <QVector>
#include <QString>
class ShowTypingCode : public QThread
{
public:
  explicit ShowTypingCode(QObject *parent, const QVector<QString>&);
private:
  QVector<QString> v;
  void run();
};

#endif // SHOWTYPINGCODE_H
