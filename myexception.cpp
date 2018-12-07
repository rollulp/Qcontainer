#include "myexception.h"

MyException::MyException(string msg)
    : msg(msg)
{}

string MyException::what() const {
    return msg;
}
