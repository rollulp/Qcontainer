#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <QString>

class MyException
{
    const QString msg;
public:
    MyException(QString msg);
    QString what() const;
};

#endif // MYEXCEPTION_H
