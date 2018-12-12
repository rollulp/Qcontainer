#ifndef LISTSELECTER_H
#define LISTSELECTER_H

#include <QObject>
#include <QtWidgets>
#include <QDialog>

class ListSelecter : public QDialog {
    Q_OBJECT
    QGridLayout *grid;
public:
    ListSelecter(QWidget *parent);
};

#endif // LISTSELECTER_H
