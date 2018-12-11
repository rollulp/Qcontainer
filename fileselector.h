#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>


class FileSelector : public QDialog
{
    Q_OBJECT
private:
    QString &path;
    FileSelector(QWidget *parent, QString& path);

public:
    static QString getPathFromUserInput();

};

#endif // FILESELECTOR_H
