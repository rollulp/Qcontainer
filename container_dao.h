#ifndef CONTAINER_DAO_H
#define CONTAINER_DAO_H
#include <type_traits>
#include "container.h"
#include "dao.h"

template <typename T>
class Container_DAO : virtual public Container<T>, public DAO {
    static_assert(std::is_base_of<DAO, T>::value, "Container_DAO<T> works only if T extends DAO");
public:
    Container_DAO(size_t n = 0) : Container<T>(n) {}

    virtual QJsonObject getJSON () const;
    virtual void loadFromJSON (const QJsonObject &);
};

#endif // CONTAINER_DAO_H
