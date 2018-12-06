#include "myexception.h"

MyException::MyException(QString msg)
    : msg(msg)
{}

QString MyException::what() const {
    return msg;
}
