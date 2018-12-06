#ifndef DAO_H
#define DAO_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

class DAO
{
public:
    typedef QJsonObject JSON;
    typedef QString string;

    static void setPath(const string & s);
    static string getPath();

    virtual JSON getJSON () const = 0;
    virtual void loadFromJSON (const JSON &) = 0;
};

#endif // DAO_H
