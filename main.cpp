#include "mainwindow.h"
#include "fileselector.h"
#include "dao.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    FileSelector *fileSelector = new FileSelector;
    fileSelector->show();
    if ( !a.exec() ) return 1;

    DAO::setPath( fileSelector->getFilePath() );

    delete fileSelector;

    MainWindow w;
    w.show();

    return a.exec();
}
