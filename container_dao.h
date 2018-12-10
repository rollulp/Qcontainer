#ifndef CONTAINER_DAO_H
#define CONTAINER_DAO_H
#include <type_traits>
#include "container.h"
#include "dao.h"
#include "deeptr_dao_dildo.h"
#include "myexception.h"

template <typename T>
class Container_DAO : virtual public Container<T>, public DAO {
    static_assert(std::is_base_of<DAO, DeepPtr<T> >::value, "Container_DAO<T> works only if T extends DAO");
public:
    using Container<T>::Container;

    QJsonObject getJSON() const {
        QJsonObject json;
        QJsonArray jsonArray;
        json["len"] = static_cast<int>(this->size());
        for (size_t i = 0; i < this->size(); i++)
            jsonArray.append( static_cast<DAO*>(&(this->getDeepPtr(i)))->getJSON() );
        json["data"] = jsonArray;
        return json;
    }

    void loadFromJSON (const QJsonObject & json) {
       QJsonArray array = json["data"].toArray();
       if (array.size() != json["len"].toInt())
           throw MyException("JSON in an odd state, cannot read");
       Container_DAO<T>::resize(array.size());
       for(int i = 0; i < array.size(); i++)
           static_cast<DAO*>(&(this->getDeepPtr(i)))->loadFromJSON(array[i].toObject());
    }
};

#endif // CONTAINER_DAO_H
