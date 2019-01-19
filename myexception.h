#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>
#include <exception>

//!
//! Ho usato questa classe per includere header temporanei,
//! come iostream o QDebug, o definire costanti. Alla fine
//! ho lasciato la classe qui.
//!
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
