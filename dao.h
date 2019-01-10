#ifndef DAO_H
#define DAO_H

#include <string>
using std::string;

#include <QJsonObject>
#include <QJsonArray>

class DAO
{
public:
    // typedefs qui per cambiare più in fretta in caso non
    // si usasse più Qt
    typedef QJsonObject JSON;
    typedef QJsonArray JArray;

    static void setPath(const string & s);
    static string getPath();
    static JSON loadFile();
    static void writeFile(const JSON &json);
    static JSON string2json(const string& s);

    virtual JSON getJSON () const = 0;
    virtual void loadFromJSON (const JSON &) = 0;
};

#endif // DAO_H
