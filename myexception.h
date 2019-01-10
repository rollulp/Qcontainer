#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>
#include <exception>

#include <iostream>
using namespace std;

using std::string;

class MyException : public std::exception
{
    const string msg;
public:
    MyException(string msg);
    const char* what() const noexcept;
};

#endif // MYEXCEPTION_H
