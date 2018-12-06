#ifndef CONTAINER_DAO_H
#define CONTAINER_DAO_H
#include <type_traits>
#include "container.h"
#include "dao.h"
#include "myexception.h"

template <typename T>
class Container_DAO : virtual public Container<T>, public DAO {
    static_assert(std::is_base_of<DAO, DeepPtr<T> >::value, "Container_DAO<T> works only if T extends DAO");
public:
    using Container<T>::Container;

    QJsonObject getJSON() const {
        QJsonObject containerJSON;
        QJsonArray dataJSON;
        containerJSON["len"] = static_cast<int>(this->size());
        for (size_t i = 0; i < this->size(); i++)
            dataJSON.append( static_cast<DAO*>(&(this->getDeepPtr(i)))->getJSON() );
        containerJSON["data"] = dataJSON;
        return containerJSON;
    }

    void loadFromJSON (const QJsonObject & json) {
       size_t len = static_cast<size_t>(json["len"].toInt());
       QJsonArray array = json["data"].toArray();
       if (array.size() != len)
           throw MyException("JSON in an odd state, cannot read");
//       for(size_t i = 0; i < len; i++)
//           push_back(array[i].);
    }
};

#endif // CONTAINER_DAO_H
