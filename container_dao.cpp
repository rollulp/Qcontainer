#include "container_dao.h"


//TODO
template <typename T>
QJsonObject Container_DAO<T>::getJSON () const {
    QJsonObject containerJSON;
    QJsonArray dataJSON;
    containerJSON["len"] = this->size();
    for (size_t i = 0; i < this->size(); i++)
        dataJSON.append( static_cast<DAO*>((*this)[i]) );
    containerJSON["data"] = dataJSON;
    return containerJSON;
}
template <typename T>
void Container_DAO<T>::loadFromJSON (const QJsonObject &) {
}
