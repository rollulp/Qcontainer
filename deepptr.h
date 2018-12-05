#ifndef DEEPPTR_H
#define DEEPPTR_H

template <typename T>
class DeepPtr {
    T* obj;
public:
    DeepPtr() : obj(nullptr) {}
    DeepPtr(const T &t) : obj(new T(t)) {} // copia la referenza
    DeepPtr(const T *t) : obj(t) {} // assorbe il puntatore (DeepPtr<T> ptr = new T; diventa possibile)
    DeepPtr(const DeepPtr & ptr) : obj(new T(obj)) {}
    T& operator *(void) {
        return *obj;
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
