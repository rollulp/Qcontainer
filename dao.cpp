#include <QFile>
#include <QJsonDocument>
#include "dao.h"
#include "myexception.h"

static string filename;

void DAO::setPath(const string & s) {
    filename = s;
}
string DAO::getPath() {
    return filename;
}

DAO::JSON DAO::loadFile() {
    QFile jsonFile(QString::fromStdString(filename));
    jsonFile.open(QFile::ReadOnly);
    if (! jsonFile.isReadable())
        throw MyException("cannot read save file, is the path correct?");
    return QJsonDocument().fromJson(jsonFile.readAll()).object();
}

void DAO::writeFile(const JSON &json) {
    QFile jsonFile(QString::fromStdString(filename));
    jsonFile.open(QFile::WriteOnly);
    if (! jsonFile.isWritable())
        throw MyException("cannot write save file, is the path correct?");
    QJsonDocument document;
    document.setObject(json);
    jsonFile.write(document.toJson());
}

DAO::JSON DAO::string2json(const string &s) {
     return QJsonDocument().fromJson( QString::fromStdString(s).toUtf8() ).object();
}
