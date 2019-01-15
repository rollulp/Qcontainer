#include "container_dildo.h"

Container_Dildo::JSON Container_Dildo::getJSONFromDildo(const typename Container<Dildo>::iterator &d) const {
    JSON json;
    json["type"] = d->getCategory();
    json["price"] = d->getPrice();
    json["diam"] = d->getDiam();
    json["len"] =  d->getLength();
    json["color"] = static_cast<int>( d->getColor() );
    json["img64"] = QString::fromStdString(d->getImg());
    json["title"] = QString::fromStdString(d->getTitle());

    /* siccome ho 'virtual getCathegory()', sarebbe molto più efficiente usare quella
     * per sapere a cosa castare. Ma siccome lo scopo dell' esercizio è di
     * esplorare il polimorfismo, giù di 'dinamic_cast<T*>' !! */
    if ( auto ptr = dynamic_cast<const DoubleDildo*>(&*d) )
        json["diam2"] = ptr->getDiam2();
    else if ( auto ptr =dynamic_cast<const ElectricDildo*>(&*d) ) {
        json["watts"] = ptr->getWatts();
        if ( auto ptr2 = dynamic_cast<const ThermoDildo*>(ptr) )
            json["temp"] = ptr2->getTemp();
        if ( auto ptr2 = dynamic_cast<const InternalVibrator*>(ptr) )
            json["freq"] = ptr2->getFrequency();
    }
    return json;
}

void Container_Dildo::addDildoFromJSON (const JSON &json) {
    auto d = json["type"].toString();
    Dildo* dildo;
    if (d == SimpleDildo::category)
        dildo = new SimpleDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["title"].toString().toStdString());
    else if (d == DoubleDildo::category)
        dildo = new DoubleDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["title"].toString().toStdString(), json["diam2"].toInt());
    else if (d == ThermoDildo::category)
        dildo = new ThermoDildo(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["title"].toString().toStdString(), json["watts"].toInt(), json["temp"].toInt());
    else if (d == InternalVibrator::category)
        dildo = new InternalVibrator(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["title"].toString().toStdString(), json["watts"].toInt(), json["freq"].toInt());
    else if (d == DildoDeluxe::category)
        dildo = new DildoDeluxe(json["price"].toInt(), json["diam"].toInt(), json["len"].toInt(), (Dildo::Color)(json["color"].toInt()), json["img64"].toString().toStdString(), json["title"].toString().toStdString(), json["watts"].toInt(), json["freq"].toInt(), json["temp"].toInt());
    else throw MyException("wut");

    Container<Dildo>::push_back(dildo);
}

Container_Dildo::JSON Container_Dildo::getJSON() const {
    JSON json;
    JArray jsonArray;
    for (auto it = Container<Dildo>::begin(); it; ++it)
        jsonArray.append( getJSONFromDildo(it) );
    json["data"] = jsonArray;
    return json;
}

void Container_Dildo::loadFromJSON (const QJsonObject & json) {
   JArray array = json["data"].toArray();
   for(int i = 0; i < array.size(); i++)
       addDildoFromJSON(array[i].toObject());
}
