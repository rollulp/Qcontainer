#ifndef CONTAINER_DAO_H
#define CONTAINER_DAO_H
#include "container.h"
#include "dao.h"

template <typename T>
class Container_DAO : virtual public Container<T>, public DAO {
public:
    Container_DAO(size_t n = 0) : Container<T>(n) {}

    virtual QJsonObject getJSON () const {
        return QJsonObject();
    }
    virtual void loadFromJSON (const QJsonObject &) {

    }
};

#endif // CONTAINER_DAO_H
