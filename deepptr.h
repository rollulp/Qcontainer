#ifndef DEEPPTR_H
#define DEEPPTR_H

template <typename T>
class DeepPtr {
    T* obj;
public:
    DeepPtr() : obj(nullptr) {}
    DeepPtr(const T &t) : obj(new T(t)) {} // copia la referenza
    DeepPtr(const DeepPtr & ptr) : obj(new T(obj)) {}
    DeepPtr& operator = (T* rhs) {
        obj = rhs;
    }
    //preferisco un .get() a un overload di operator *(void)
    T& get() {
        if (obj)
            return *obj;
        return *obj; // TODO ERR nullptrException
    }
    ~DeepPtr() {
        if (obj)
            delete obj;
    }
    // per muovere i puntatori senza copiare l'oggetto
    // cancella  il proprio, e assorbe l'altro, che diventa nullo
    void eat(DeepPtr & rhs) {
        if (obj)
            delete obj;
        obj = rhs.obj;
        rhs.obj = nullptr;
    }
};

#endif // DEEPPTR_H
