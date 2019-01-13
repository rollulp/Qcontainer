#ifndef DETAILSLAYOUT_H
#define DETAILSLAYOUT_H
#include <QtWidgets>
#include "dildo.h"
#include "defaults.h"
#include "container.h"

class DetailsLayout;

class EditableLayout : public QHBoxLayout {
    Q_OBJECT
    QLabel label;
    QSpinBox value;
    void (Dildo::*setter) (int);
public:
    EditableLayout(QString field, int initial_val, int min = defaults::spinner_min, int max = defaults::spinner_max);
    int getValue() const;
};

class DetailsLayout : public QVBoxLayout {


    Q_OBJECT
    QLabel image;
    Container<EditableLayout> lines;
    QPushButton saveBtn;
    Dildo *dildo;

public:
    DetailsLayout(QWidget *parent = 0);
    void showDildo(Dildo &dildo);
    void clear();

};

#endif // DETAILSLAYOUT_H
