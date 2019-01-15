#ifndef DAO_H
#define DAO_H

#include <string>
using std::string;

#include <QJsonObject>
#include <QJsonArray>

/*!
 * \class DAO
 * Classe astratta per gestire oggetti che possono essere salvati/caricati
 * a partire da JSON scritto in un file
 */
class DAO {
public:
    // typedefs qui per cambiare più in fretta in caso non
    // si usasse più Qt, per non vincolarsi
    typedef QJsonObject JSON;
    typedef QJsonArray JArray;

    /// imposta il percorso del file, statico per tutto il programma
    static void setPath(const string & s);

    /// mostra in percorso del file impostato, statico per tutto il programma
    static string getPath();

    /// leggi il JSON dal file
    static JSON loadFile();

    /// scrivi il JSON nel file
    static void writeFile(const JSON &json);

    static JSON string2json(const string& s);

    /// ritorna il JSON del file, virtuale pura
    virtual JSON getJSON () const = 0;

    /// carica dal JSON, virtuale pura
    virtual void loadFromJSON (const JSON &) = 0;
};

#endif // DAO_H
