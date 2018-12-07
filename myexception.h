#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>

using std::string;

class MyException
{
    const string msg;
public:
    MyException(string msg);
    string what() const;
};

#endif // MYEXCEPTION_H
