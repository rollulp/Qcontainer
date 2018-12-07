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

#ifdef DILDO_H
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
        json["price"] = obj->getPrice();
        json["diam"] = obj->getDiam();
        json["len"] =  obj->getLength();
        json["color"] = static_cast<int>( obj->getColor() );
        json["img64"] = QString::fromStdString(obj->getImg());

        /* siccome ho 'virtual getCathegory()', sarebbe molto più efficiente usare quella
         * per sapere a cosa castare. Ma siccome lo scopo dell' esercizio è di
         * esplorare il polimorfismo, giù di 'dinamic_cast<T*>' !! */
        if ( auto ptr = dynamic_cast<DoubleDildo*>(obj) )
            json["diam2"] = ptr->getDiam2();
        else if ( auto ptr =dynamic_cast<ElectricDildo*>(obj) ) {
            json["watts"] = ptr->getWatts();
            if ( auto ptr2 = dynamic_cast<ThermoDildo*>(ptr) )
                json["temp"] = ptr2->getTemp();
            if ( auto ptr2 = dynamic_cast<InternalVibrator*>(ptr) )
                json["freq"] = ptr2->getFrequency();
        }
        return json;

    }
    virtual void loadFromJSON (const JSON &json) {
        DAO::string d = json["type"].toString();
        if (d == SimpleDildo::category)
            obj = new SimpleDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), "");
        else if (d == DoubleDildo::category)
            obj = new DoubleDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), "", json["diam2"].toInt());
        else if (d == ThermoDildo::category)
            obj = new ThermoDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), "", json["watts"].toInt(), json["temp"].toInt());
        else if (d == InternalVibrator::category)
            obj = new InternalVibrator(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), "", json["watts"].toInt(), json["freq"].toInt());
        else if (d == DildoDeluxe::category)
            obj = new DildoDeluxe(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), "", json["watts"].toInt(), json["temp"].toInt(), json["freq"].toInt());

    }
};
#endif // DILDO_H

#endif // DEEPPTR_H
