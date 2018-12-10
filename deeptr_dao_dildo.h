#ifndef DEPPTR_DAO_DILDO_H
#define DEPPTR_DAO_DILDO_H

#include "deepptr.h"
#include "dao.h"
#include "dildo.h"
#include "myexception.h"


template<>
class DeepPtr<Dildo> : public __DeepPtr__<Dildo>, public DAO {
    void virtualizer() const {}
    using __DeepPtr__::obj;
public:
/*constructors & stuff*/
    DeepPtr() : __DeepPtr__() {}
    DeepPtr(const DeepPtr<Dildo> & ptr) : __DeepPtr__(ptr.get().clone()) {}

    DeepPtr& operator = (const Dildo* rhs) {
        obj = rhs->clone();
        return *this;
    }

/*DAO virtual stuff*/
    virtual JSON getJSON () const {
        JSON json;
        json["type"] = get().getCategory();
        json["price"] = get().getPrice();
        json["diam"] = get().getDiam();
        json["len"] =  get().getLength();
        json["color"] = static_cast<int>( get().getColor() );
        json["img64"] = QString::fromStdString(get().getImg());

        /* siccome ho 'virtual getCathegory()', sarebbe molto più efficiente usare quella
         * per sapere a cosa castare. Ma siccome lo scopo dell' esercizio è di
         * esplorare il polimorfismo, giù di 'dinamic_cast<T*>' !! */
        if ( auto ptr = dynamic_cast<DoubleDildo*>(&get()) )
            json["diam2"] = ptr->getDiam2();
        else if ( auto ptr =dynamic_cast<ElectricDildo*>(&get()) ) {
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
            obj = new SimpleDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString());
        else if (d == DoubleDildo::category)
            obj = new DoubleDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["diam2"].toInt());
        else if (d == ThermoDildo::category)
            obj = new ThermoDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["watts"].toInt(), json["temp"].toInt());
        else if (d == InternalVibrator::category)
            obj = new InternalVibrator(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["watts"].toInt(), json["freq"].toInt());
        else if (d == DildoDeluxe::category)
            obj = new DildoDeluxe(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["watts"].toInt(), json["temp"].toInt(), json["freq"].toInt());

    }
};


#endif // DEPPTR_DAO_DILDO_H
