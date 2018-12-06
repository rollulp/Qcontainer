#ifndef DEEPPTR_H
#define DEEPPTR_H
#include "dao.h"
#include "dildo.h"

template <typename T>
class DeepPtr {
    T* obj;
public:
    DeepPtr() : obj(nullptr) {}
    DeepPtr(const T &t) : obj(new T(t)) {} // copia la referenza
    DeepPtr(const DeepPtr & ptr) : obj(new T(obj)) {}
    ~DeepPtr() {
        if (obj)
            delete obj;
    }
    DeepPtr& operator = (T* rhs) {
        obj = rhs;
        return *this;
    }
    //preferisco un .get() a un overload di operator *(void)
    T& get() const {
        if (obj)
            return *obj;
        return *obj; // TODO ERR nullptrException
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

template<>
class DeepPtr<Dildo> : public DAO {
    Dildo *obj;
public:
/*constructors & stuff*/
    DeepPtr() : obj(nullptr) {}
    DeepPtr(const DeepPtr<Dildo> & ptr) : obj(ptr.get().clone()) {}
    ~DeepPtr() {
        if (obj)
            delete obj;
    }
    DeepPtr& operator = (const Dildo* rhs) {
        obj = rhs->clone();
        return *this;
    }

/*methods*/
    //preferisco un .get() a un overload di operator *(void)
    Dildo& get() const {
        if (obj)
            return *obj;
        return *obj; // TODO ERR nullptrException
    }
    void eat(DeepPtr<Dildo> & rhs) {
        if (obj)
            delete obj;
        obj = rhs.obj;
        rhs.obj = nullptr;
    }

/*DAO virtual stuff*/
    virtual JSON getJSON () const {
        JSON json;
        json["type"] = obj->getCategory();
        return json;

    }
    virtual void loadFromJSON (const JSON &json) {
        string s = json["type"].toString();
    }
};

#endif // DEEPPTR_H
