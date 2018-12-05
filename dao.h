#ifndef DAO_H
#define DAO_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

class DAO
{
public:
    static void setPath(const QString & s);
    static QString getPath();

    virtual QJsonObject getJSON () const = 0;
    virtual void loadFromJSON (const QJsonObject &) = 0;
};

#endif // DAO_H
