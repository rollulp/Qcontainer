#ifndef DEEPPTR_H
#define DEEPPTR_H
#include "dao.h"
#include "myexception.h"

template <typename T>
class __DeepPtr__ {
    void virtual virtualizer() const = 0;
protected:
    T* obj;
public:
    __DeepPtr__(T* t = nullptr) : obj(t) {} // absorbs the pointer
    __DeepPtr__(const T &t) : obj(new T(t)) {} // copies the reference
    template<typename U = T>
    __DeepPtr__(const __DeepPtr__ & ptr,
                typename std::enable_if< std::is_copy_constructible<U>::value, void>::type* = 0) : obj(new T(ptr)) {}
    template<typename U = T>
    __DeepPtr__(const __DeepPtr__ & ptr,
                typename std::enable_if< ! std::is_copy_constructible<U>::value, void>::type* = 0) : obj(nullptr) {}
    ~__DeepPtr__() {
        if (obj)
            delete obj;
    }
    virtual __DeepPtr__& operator = (T* rhs) {
        obj = rhs;
        return *this;
    }
    //preferisco un .get() a un overload di operator *(void)
    T& get() const {
        if (obj)
            return *obj;
        throw MyException("Derefercing null ptr");
    }
    // per muovere i puntatori senza copiare l'oggetto
    // cancella  il proprio, e assorbe l'altro, che diventa nullo
    void eat(__DeepPtr__ & rhs) {
        if (obj)
            delete obj;
        obj = rhs.obj;
        rhs.obj = nullptr;
    }
};

template<typename T>
class DeepPtr : __DeepPtr__<T> {
    using __DeepPtr__<T>::__DeepPtr__;
    void virtualizer() const {}
};

#endif // DEEPPTR_H
