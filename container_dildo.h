#ifndef CONTAINER_DAO_H
#define CONTAINER_DAO_H
#include <type_traits>
#include "container.h"
#include "dao.h"
#include "dildo.h"
#include "myexception.h"

/*!
 * \class Container_Dildo
 * eredita da Container<Dildo> e da DAO, aggiungendo qualche metodo
 * per gesitre correttamente in salvataggio/ripristino in JSON del file
 */
class Container_Dildo : virtual public Container<Dildo>, public DAO {

    /// da un dildo ne estrae il JSON
    JSON getJSONFromDildo(const typename Container<Dildo>::iterator &d) const;

    /// aggiunge alla lista un dildo a partire dalla forma JSON
    void addDildoFromJSON (const JSON &json);

public:
    /// eredito i costruttori
    using Container<Dildo>::Container;

    /// \return JSON dell' intero Container
    JSON getJSON() const;

    /// Carico il Container a partire dalla sua forma in JSON
    void loadFromJSON (const QJsonObject & json);

};

#endif // CONTAINER_DAO_H
