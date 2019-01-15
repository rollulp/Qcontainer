#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>
#include <exception>

using std::string;

/*!
 * \class MyException
 * \brief exception class
 */
class MyException : public std::exception {
    const string msg;
public:
    MyException(string msg);
    const char* what() const noexcept;
};

#endif // MYEXCEPTION_H
