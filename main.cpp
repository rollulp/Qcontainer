#include "mainwindow.h"
#include <QApplication>
#include <fileselector.h>
#include "dao.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString path = FileSelector::getPathFromUserInput();
    if ( path == "@nopath@" ) return 1;
    DAO::setPath( path.toStdString() );

    MainWindow w;
    w.show();

    return a.exec();
}
