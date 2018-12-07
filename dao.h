#ifndef DAO_H
#define DAO_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

class DAO
{
public:
    // typedefs qui per cambiare più in fretta in caso non
    // si usasse più Qt
    typedef QJsonObject JSON;
    typedef QString string;

    static void setPath(const string & s);
    static string getPath();
    static JSON loadFile();
    static void writeFile(const JSON &json);
    static JSON string2json(const QString& s);

    virtual JSON getJSON () const = 0;
    virtual void loadFromJSON (const JSON &) = 0;
};

#endif // DAO_H
