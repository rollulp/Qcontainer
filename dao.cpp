#include <QFile>
#include <QJsonDocument>
#include "dao.h"
#include "myexception.h"

static QString filename;

void DAO::setPath(const QString & s) {
    filename = s;
}
QString DAO::getPath() {
    return filename;
}

DAO::JSON DAO::loadFile() {
    QFile jsonFile(filename);
    jsonFile.open(QFile::ReadOnly);
    if (! jsonFile.isReadable())
        throw MyException("cannot read save file, is the path correct?");
    return QJsonDocument().fromJson(jsonFile.readAll()).object();
}

void DAO::writeFile(const JSON &json) {
    QFile jsonFile(filename);
    jsonFile.open(QFile::WriteOnly);
    if (! jsonFile.isWritable())
        throw MyException("cannot write save file, is the path correct?");
    QJsonDocument document;
    document.setObject(json);
    jsonFile.write(document.toJson());
}
