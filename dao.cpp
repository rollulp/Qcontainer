#include "dao.h"

static QString folder;
void DAO::setPath(const QString & s) {
    folder = s;
}
QString DAO::getPath() {
    return folder;
}
