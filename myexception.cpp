#include "myexception.h"

MyException::MyException(string msg)
    : msg(msg)
{}

const char* MyException::what() const noexcept {
    return msg.c_str();
}
